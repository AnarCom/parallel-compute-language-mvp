/**
 * @file main.cpp
 * @brief Data Processing Pipeline Demo
 * 
 * This example demonstrates the enhanced runtime capabilities:
 * - Event logging with InMemoryEventLogger
 * - Error handling with different policies
 * - Lifecycle management and graceful shutdown
 * - Multi-stage pipeline processing
 * 
 * Pipeline Architecture:
 * 
 *   DataGenerator → Validator → Transformer → Aggregator → Reporter
 *        |             |            |             |            |
 *     (raw data)   (validated)  (processed)   (aggregated)  (results)
 * 
 * The pipeline simulates a data processing system where:
 * - DataGenerator: Produces batches of sensor readings
 * - Validator: Checks data quality (may fail on invalid data)
 * - Transformer: Normalizes and enriches data
 * - Aggregator: Computes statistics across batches
 * - Reporter: Outputs final results and triggers shutdown
 */

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

#include <runtime/reactor/common/interface.hpp>
#include <runtime/reactor/common/logging.hpp>
#include <runtime/reactor/common/event_logger.hpp>
#include <runtime/reactor/common/error_handler.hpp>
#include <runtime/reactor/common/lifecycle.hpp>
#include <runtime/reactor/parallel_improved/repository.hpp>

using namespace reactor;

// ============================================================================
// Configuration Constants
// ============================================================================

constexpr size_t NUM_BATCHES = 10;           // Number of data batches to process
constexpr size_t BATCH_SIZE = 100;           // Readings per batch
constexpr double INVALID_DATA_RATE = 0.05;   // 5% of data will be invalid
constexpr double SENSOR_MIN = 0.0;           // Minimum sensor value
constexpr double SENSOR_MAX = 100.0;         // Maximum sensor value
constexpr double INVALID_THRESHOLD = 150.0;  // Values above this are invalid

// ============================================================================
// Data Structures
// ============================================================================

/**
 * @brief Represents a sensor reading with metadata
 */
struct SensorReading {
    uint64_t id;
    double value;
    std::chrono::system_clock::time_point timestamp;
    
    SensorReading(uint64_t id, double value)
        : id(id), value(value), timestamp(std::chrono::system_clock::now()) {}
};

/**
 * @brief Statistics computed over a batch of readings
 */
struct BatchStatistics {
    size_t count;
    double min;
    double max;
    double mean;
    double stddev;
    
    BatchStatistics() : count(0), min(0), max(0), mean(0), stddev(0) {}
};

// ============================================================================
// Utility Functions
// ============================================================================

/**
 * @brief Convert a vector of SensorReading to reactor Objects
 */
Objects ReadingsToObjects(const std::vector<SensorReading>& readings) {
    Objects result;
    for (const auto& reading : readings) {
        // Store as tuple: (id, value, timestamp_ms)
        auto timestamp_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            reading.timestamp.time_since_epoch()).count();
        
        Objects tuple_elements;
        tuple_elements.push_back(Object::Int(reading.id));
        tuple_elements.push_back(Object::Int(static_cast<int64_t>(reading.value * 1000))); // Store as millis
        tuple_elements.push_back(Object::Int(timestamp_ms));
        
        result.push_back(Object::Tuple(std::move(tuple_elements)));
    }
    return result;
}

/**
 * @brief Convert reactor Objects back to SensorReading vector
 */
std::vector<SensorReading> ObjectsToReadings(const Objects& objects) {
    std::vector<SensorReading> readings;
    for (const auto& obj : objects) {
        const auto& tuple = obj.AsTuple();
        uint64_t id = tuple[0].AsInt();
        double value = tuple[1].AsInt() / 1000.0;
        readings.emplace_back(id, value);
    }
    return readings;
}

/**
 * @brief Compute statistics for a batch of readings
 */
BatchStatistics ComputeStatistics(const std::vector<SensorReading>& readings) {
    BatchStatistics stats;
    if (readings.empty()) return stats;
    
    stats.count = readings.size();
    stats.min = readings[0].value;
    stats.max = readings[0].value;
    
    double sum = 0.0;
    for (const auto& reading : readings) {
        stats.min = std::min(stats.min, reading.value);
        stats.max = std::max(stats.max, reading.value);
        sum += reading.value;
    }
    
    stats.mean = sum / stats.count;
    
    // Compute standard deviation
    double variance_sum = 0.0;
    for (const auto& reading : readings) {
        double diff = reading.value - stats.mean;
        variance_sum += diff * diff;
    }
    stats.stddev = std::sqrt(variance_sum / stats.count);
    
    return stats;
}

// ============================================================================
// Reactor Implementations
// ============================================================================

/**
 * @brief Generates batches of sensor data
 * 
 * Produces NUM_BATCHES batches of sensor readings. Some readings are
 * intentionally invalid to demonstrate error handling.
 */
class DataGenerator : public Runnable {
public:
    DataGenerator() : batch_count_(0) {}
    
    void operator()(Objects inputs, Objects context) override {
        std::cout << "\n[DataGenerator] Starting data generation..." << std::endl;
        
        auto validator_channel = context[0].AsChannel();
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> value_dist(SENSOR_MIN, SENSOR_MAX);
        std::uniform_real_distribution<> invalid_dist(0.0, 1.0);
        
        for (size_t batch = 0; batch < NUM_BATCHES; ++batch) {
            std::vector<SensorReading> readings;
            
            for (size_t i = 0; i < BATCH_SIZE; ++i) {
                uint64_t id = batch * BATCH_SIZE + i;
                double value;
                
                // Occasionally generate invalid data
                if (invalid_dist(gen) < INVALID_DATA_RATE) {
                    value = INVALID_THRESHOLD + value_dist(gen);
                    std::cout << "[DataGenerator] Generated invalid reading: id=" 
                              << id << ", value=" << value << std::endl;
                } else {
                    value = value_dist(gen);
                }
                
                readings.emplace_back(id, value);
            }
            
            // Convert to Objects and send
            // Create list with proper tuple type
            std::vector<Type> tuple_types = {Type::Int(), Type::Int(), Type::Int()};
            auto batch_obj = Object::List(ReadingsToObjects(readings), Type::Tuple(tuple_types));
            validator_channel->Push(batch_obj);
            
            std::cout << "[DataGenerator] Sent batch " << (batch + 1) 
                      << "/" << NUM_BATCHES << " (" << readings.size() 
                      << " readings)" << std::endl;
            
            // Small delay to simulate real-time data generation
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        
        std::cout << "[DataGenerator] Completed data generation" << std::endl;
    }
    
    uint64_t GetID() const noexcept override { return 0; }
    
private:
    size_t batch_count_;
};

/**
 * @brief Validates sensor readings
 * 
 * Filters out invalid readings and passes valid ones to the transformer.
 * Demonstrates error handling when invalid data is detected.
 */
class Validator : public Runnable {
public:
    Validator() : total_processed_(0), total_invalid_(0) {}
    
    void operator()(Objects inputs, Objects context) override {
        auto batch_obj = inputs[0];
        auto transformer_channel = context[0].AsChannel();
        
        auto readings = ObjectsToReadings(batch_obj.AsList());
        std::vector<SensorReading> valid_readings;
        
        for (const auto& reading : readings) {
            total_processed_++;
            
            if (reading.value > INVALID_THRESHOLD) {
                total_invalid_++;
                std::cerr << "[Validator] INVALID reading detected: id=" 
                          << reading.id << ", value=" << reading.value << std::endl;
                
                // Simulate error handling - throw exception for invalid data
                if (total_invalid_ % 3 == 0) {  // Every 3rd invalid reading causes exception
                    throw std::runtime_error(
                        "Critical validation failure: reading " + 
                        std::to_string(reading.id) + " = " + 
                        std::to_string(reading.value));
                }
            } else {
                valid_readings.push_back(reading);
            }
        }
        
        if (!valid_readings.empty()) {
            std::vector<Type> tuple_types = {Type::Int(), Type::Int(), Type::Int()};
            auto valid_batch = Object::List(ReadingsToObjects(valid_readings), Type::Tuple(tuple_types));
            transformer_channel->Push(valid_batch);
            
            std::cout << "[Validator] Validated batch: " << valid_readings.size() 
                      << " valid, " << (readings.size() - valid_readings.size()) 
                      << " invalid (total invalid: " << total_invalid_ << ")" << std::endl;
        }
    }
    
    uint64_t GetID() const noexcept override { return 1; }
    
private:
    size_t total_processed_;
    size_t total_invalid_;
};

/**
 * @brief Transforms and normalizes sensor data
 * 
 * Applies transformations to validated data:
 * - Normalizes values to 0-1 range
 * - Applies smoothing
 */
class Transformer : public Runnable {
public:
    Transformer() : batches_processed_(0) {}
    
    void operator()(Objects inputs, Objects context) override {
        auto batch_obj = inputs[0];
        auto aggregator_channel = context[0].AsChannel();
        
        auto readings = ObjectsToReadings(batch_obj.AsList());
        
        // Normalize values to 0-1 range
        for (auto& reading : readings) {
            reading.value = (reading.value - SENSOR_MIN) / (SENSOR_MAX - SENSOR_MIN);
        }
        
        // Send transformed data
        std::vector<Type> tuple_types = {Type::Int(), Type::Int(), Type::Int()};
        auto transformed_batch = Object::List(ReadingsToObjects(readings), Type::Tuple(tuple_types));
        aggregator_channel->Push(transformed_batch);
        
        batches_processed_++;
        std::cout << "[Transformer] Transformed batch " << batches_processed_ 
                  << " (" << readings.size() << " readings normalized)" << std::endl;
    }
    
    uint64_t GetID() const noexcept override { return 2; }
    
private:
    size_t batches_processed_;
};

/**
 * @brief Aggregates statistics across batches
 * 
 * Computes running statistics and accumulates results.
 */
class Aggregator : public Runnable {
public:
    Aggregator() : batches_aggregated_(0), total_readings_(0) {}
    
    void operator()(Objects inputs, Objects context) override {
        auto batch_obj = inputs[0];
        auto reporter_channel = context[0].AsChannel();
        
        auto readings = ObjectsToReadings(batch_obj.AsList());
        auto stats = ComputeStatistics(readings);
        
        batches_aggregated_++;
        total_readings_ += stats.count;
        
        // Store statistics
        all_stats_.push_back(stats);
        
        std::cout << "[Aggregator] Batch " << batches_aggregated_ 
                  << " stats: count=" << stats.count
                  << ", mean=" << stats.mean
                  << ", stddev=" << stats.stddev
                  << ", range=[" << stats.min << ", " << stats.max << "]" << std::endl;
        
        // After processing all expected batches, send summary to reporter
        if (batches_aggregated_ >= NUM_BATCHES) {
            // Create summary object
            Objects summary;
            summary.push_back(Object::Int(total_readings_));
            summary.push_back(Object::Int(batches_aggregated_));
            
            auto summary_obj = Object::Tuple(std::move(summary));
            reporter_channel->Push(summary_obj);
            
            std::cout << "[Aggregator] Sent final summary to reporter" << std::endl;
        }
    }
    
    uint64_t GetID() const noexcept override { return 3; }
    
private:
    size_t batches_aggregated_;
    size_t total_readings_;
    std::vector<BatchStatistics> all_stats_;
};

/**
 * @brief Reports final results and triggers shutdown
 * 
 * Displays pipeline results and demonstrates graceful shutdown.
 */
class Reporter : public Runnable {
public:
    Reporter(ImprovedRepository* repo) : repo_(repo) {}
    
    void operator()(Objects inputs, Objects context) override {
        auto summary = inputs[0].AsTuple();
        size_t total_readings = summary[0].AsInt();
        size_t total_batches = summary[1].AsInt();
        
        std::cout << "\n" << std::string(70, '=') << std::endl;
        std::cout << "PIPELINE EXECUTION COMPLETE" << std::endl;
        std::cout << std::string(70, '=') << std::endl;
        std::cout << "Total readings processed: " << total_readings << std::endl;
        std::cout << "Total batches processed:  " << total_batches << std::endl;
        std::cout << std::string(70, '=') << std::endl;
        
        // Display event log summary
        auto logger = repo_->GetEventLogger();
        if (logger) {
            auto memory_logger = std::dynamic_pointer_cast<InMemoryEventLogger>(logger);
            if (memory_logger) {
                std::cout << "\nEVENT LOG SUMMARY:" << std::endl;
                std::cout << "Total events logged: " << memory_logger->Size() << std::endl;
                
                // Count events by type
                auto all_events = memory_logger->GetEvents();
                std::map<RuntimeEventType, size_t> event_counts;
                for (const auto& event : all_events) {
                    event_counts[event.type]++;
                }
                
                std::cout << "\nEvents by type:" << std::endl;
                for (const auto& [type, count] : event_counts) {
                    std::cout << "  " << ToString(type) << ": " << count << std::endl;
                }
            }
        }
        
        // Display error summary
        const auto& error_handler = repo_->GetErrorHandler();
        if (error_handler.HasErrors()) {
            std::cout << "\nERROR SUMMARY:" << std::endl;
            std::cout << "Total errors: " << error_handler.GetErrorCount() << std::endl;
            
            auto failed_reactions = error_handler.GetFailedReactions();
            for (const auto& result : failed_reactions) {
                std::cout << "  Reaction " << result.reaction_id << " failed: ";
                if (result.error_message) {
                    std::cout << *result.error_message << std::endl;
                } else {
                    std::cout << "(no message)" << std::endl;
                }
            }
        } else {
            std::cout << "\nNo errors occurred during execution." << std::endl;
        }
        
        std::cout << "\n" << std::string(70, '=') << std::endl;
        std::cout << "Initiating graceful shutdown..." << std::endl;
        std::cout << std::string(70, '=') << std::endl;
        
        // Trigger graceful shutdown
        repo_->Shutdown();
        
        // Exit the program (similar to quicksort example)
        // Note: Full graceful shutdown integration with Run() loop is pending
        std::exit(0);
    }
    
    uint64_t GetID() const noexcept override { return 4; }
    
private:
    ImprovedRepository* repo_;
};

/**
 * @brief Main entry point that sets up the pipeline
 */
class PipelineMain : public Runnable {
public:
    PipelineMain() {}
    
    void operator()(Objects inputs, Objects context) override {
        auto& repo = ImprovedRepository::GetRepository();
        
        std::cout << "\n" << std::string(70, '=') << std::endl;
        std::cout << "DATA PROCESSING PIPELINE DEMO" << std::endl;
        std::cout << std::string(70, '=') << std::endl;
        std::cout << "Configuration:" << std::endl;
        std::cout << "  Batches:           " << NUM_BATCHES << std::endl;
        std::cout << "  Batch size:        " << BATCH_SIZE << std::endl;
        std::cout << "  Invalid data rate: " << (INVALID_DATA_RATE * 100) << "%" << std::endl;
        std::cout << "  Error policy:      " << ToString(repo.GetErrorHandler().GetPolicy()) << std::endl;
        std::cout << std::string(70, '=') << std::endl;
        
        // Create pipeline channels
        auto validator_channel = repo.NewChannel();
        auto transformer_channel = repo.NewChannel();
        auto aggregator_channel = repo.NewChannel();
        auto reporter_channel = repo.NewChannel();
        
        // Register join-cases for each stage
        // Validator: waits for data from generator
        repo.RegisterJoinCase(
            {validator_channel},
            {Object::Channel(transformer_channel)},
            1  // Validator runnable ID
        );
        
        // Transformer: waits for validated data
        repo.RegisterJoinCase(
            {transformer_channel},
            {Object::Channel(aggregator_channel)},
            2  // Transformer runnable ID
        );
        
        // Aggregator: waits for transformed data
        repo.RegisterJoinCase(
            {aggregator_channel},
            {Object::Channel(reporter_channel)},
            3  // Aggregator runnable ID
        );
        
        // Reporter: waits for final summary
        repo.RegisterJoinCase(
            {reporter_channel},
            {},
            4  // Reporter runnable ID
        );
        
        // Trigger data generation immediately
        auto generator_trigger = repo.NewChannel();
        repo.RegisterJoinCase(
            {generator_trigger},
            {Object::Channel(validator_channel)},
            0  // DataGenerator runnable ID
        );
        
        // Push a trigger message to start the generator
        generator_trigger->Push(Object::Unit());
        
        std::cout << "\nPipeline initialized. Starting execution...\n" << std::endl;
    }
    
    uint64_t GetID() const noexcept override { return 5; }
};

// ============================================================================
// Main Function
// ============================================================================

int main(int argc, char* argv[]) {
    // Parse command line arguments for error policy
    ErrorPolicy error_policy = ErrorPolicy::IsolateReaction;
    
    if (argc > 1) {
        std::string policy_arg = argv[1];
        if (policy_arg == "fail-fast") {
            error_policy = ErrorPolicy::FailFast;
        } else if (policy_arg == "isolate") {
            error_policy = ErrorPolicy::IsolateReaction;
        } else if (policy_arg == "retry-once") {
            error_policy = ErrorPolicy::RetryOnce;
        } else if (policy_arg == "retry-backoff") {
            error_policy = ErrorPolicy::RetryWithBackoff;
        } else {
            std::cerr << "Unknown error policy: " << policy_arg << std::endl;
            std::cerr << "Valid options: fail-fast, isolate, retry-once, retry-backoff" << std::endl;
            return 1;
        }
    }
    
    try {
        auto& repo = ImprovedRepository::GetRepository();
        
        // Set up event logging
        auto event_logger = std::make_shared<InMemoryEventLogger>(10000);
        repo.SetEventLogger(event_logger);
        
        // Configure error handling
        repo.GetErrorHandler().SetPolicy(error_policy);
        
        // Create runnable map
        std::unordered_map<uint64_t, Runnable*> runnable_map = {
            {0, new DataGenerator()},
            {1, new Validator()},
            {2, new Transformer()},
            {3, new Aggregator()},
            {4, new Reporter(&repo)},
            {5, new PipelineMain()},
        };
        
        // Run the pipeline
        repo.Run(5, runnable_map);
        
        // Cleanup
        for (auto& [id, runnable] : runnable_map) {
            delete runnable;
        }
        
        std::cout << "\nPipeline execution finished successfully." << std::endl;
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "\nFATAL ERROR: " << e.what() << std::endl;
        return 1;
    }
}
