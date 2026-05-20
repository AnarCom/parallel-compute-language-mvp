# Pipeline Demo - Runtime Enhancements Showcase

**Note**: This example demonstrates event logging and error handling features. The graceful shutdown mechanism calls `std::exit(0)` similar to the quicksort example, as full lifecycle integration with the Run() loop is pending future work.

This example demonstrates the enhanced runtime capabilities integrated into the reactor system:

- **Event Logging**: Comprehensive event tracking with `InMemoryEventLogger`
- **Error Handling**: Configurable error policies (fail-fast, isolate, retry)
- **Lifecycle Management**: Graceful shutdown and state transitions
- **Multi-Stage Pipeline**: Realistic data processing workflow

## Overview

The pipeline simulates a sensor data processing system with five stages:

```
┌──────────────┐     ┌───────────┐     ┌──────────────┐     ┌────────────┐     ┌──────────┐
│ DataGenerator│────▶│ Validator │────▶│ Transformer  │────▶│ Aggregator │────▶│ Reporter │
└──────────────┘     └───────────┘     └──────────────┘     └────────────┘     └──────────┘
   Raw sensor         Quality check     Normalization      Statistics         Final results
   readings           (may fail)        & enrichment       computation        & shutdown
```

### Pipeline Stages

1. **DataGenerator**: Produces batches of sensor readings (some intentionally invalid)
2. **Validator**: Filters invalid data, demonstrates error handling
3. **Transformer**: Normalizes values to 0-1 range
4. **Aggregator**: Computes statistics (mean, stddev, min, max)
5. **Reporter**: Displays results, event logs, and triggers graceful shutdown

## Key Features Demonstrated

### 1. Event Logging

The example uses `InMemoryEventLogger` to track all runtime events:

```cpp
auto event_logger = std::make_shared<InMemoryEventLogger>(10000);
repo.SetEventLogger(event_logger);
```

Events logged include:
- Channel creation and closure
- Reaction scheduling and execution
- Message passing
- Error occurrences
- Lifecycle state transitions

The Reporter displays a summary of all logged events at the end.

### 2. Error Handling

The Validator stage intentionally throws exceptions for some invalid data to demonstrate error handling:

```cpp
// Configure error policy
repo.GetErrorHandler().SetPolicy(error_policy);
```

**Available policies:**
- `FailFast`: Terminate immediately on first error
- `IsolateReaction`: Continue execution, isolate failed reactions (default)
- `RetryOnce`: Retry failed reactions once before isolating
- `RetryWithBackoff`: Retry with exponential backoff

You can test different policies via command-line arguments.

### 3. Lifecycle Management

The pipeline demonstrates graceful shutdown:

```cpp
// Reporter triggers shutdown after processing all data
repo.Shutdown();
```

The runtime:
- Completes all pending reactions
- Closes all channels
- Transitions through lifecycle states: Running → ShuttingDown → Completed
- Cleans up resources properly

### 4. Multi-Stage Pipeline

The example shows how to build complex data flows:
- Multiple channels connecting stages
- Join-cases for synchronization
- Context passing between reactors
- Batch processing patterns

## Building the Example

### Prerequisites

- CMake 3.15 or higher
- C++20 compatible compiler
- Reactor runtime library built

### Build Steps

From the project root:

```bash
# Create build directory
mkdir -p build
cd build

# Configure
cmake ..

# Build the pipeline demo
cmake --build . --target PipelineDemo

# Or build everything
cmake --build .
```

The executable will be at: `build/examples/pipeline-demo/PipelineDemo`

## Running the Example

### Basic Execution

```bash
./build/examples/pipeline-demo/PipelineDemo
```

This runs with the default error policy (`IsolateReaction`).

### With Different Error Policies

```bash
# Fail fast on first error
./build/examples/pipeline-demo/PipelineDemo fail-fast

# Isolate failed reactions (default)
./build/examples/pipeline-demo/PipelineDemo isolate

# Retry once before isolating
./build/examples/pipeline-demo/PipelineDemo retry-once

# Retry with exponential backoff
./build/examples/pipeline-demo/PipelineDemo retry-backoff
```

## Expected Output

### Successful Execution

```
======================================================================
DATA PROCESSING PIPELINE DEMO
======================================================================
Configuration:
  Batches:           10
  Batch size:        100
  Invalid data rate: 5.0%
  Error policy:      IsolateReaction
======================================================================

Pipeline initialized. Starting execution...

[DataGenerator] Starting data generation...
[DataGenerator] Sent batch 1/10 (100 readings)
[Validator] Validated batch: 95 valid, 5 invalid (total invalid: 5)
[Transformer] Transformed batch 1 (95 readings normalized)
[Aggregator] Batch 1 stats: count=95, mean=0.487, stddev=0.289, range=[0.001, 0.998]
...

======================================================================
PIPELINE EXECUTION COMPLETE
======================================================================
Total readings processed: 950
Total batches processed:  10
======================================================================

EVENT LOG SUMMARY:
Total events logged: 247

Events by type:
  ChannelCreated: 5
  ReactionScheduled: 52
  ReactionExecuted: 52
  MessageSent: 50
  ...

ERROR SUMMARY:
Total errors: 2
  Reaction 1 failed: Critical validation failure: reading 42 = 157.3
  Reaction 1 failed: Critical validation failure: reading 89 = 162.1

======================================================================
Initiating graceful shutdown...
======================================================================

Pipeline execution finished successfully.
```

### Output Explanation

1. **Configuration**: Shows pipeline parameters and error policy
2. **Execution Logs**: Real-time progress from each stage
3. **Invalid Data**: Validator reports invalid readings detected
4. **Statistics**: Aggregator shows batch-level statistics
5. **Event Summary**: Breakdown of all logged events by type
6. **Error Summary**: Details of any errors that occurred
7. **Graceful Shutdown**: Confirms clean termination

## Configuration

You can modify the pipeline behavior in [`main.cpp`](main.cpp:30-35):

```cpp
constexpr size_t NUM_BATCHES = 10;           // Number of batches
constexpr size_t BATCH_SIZE = 100;           // Readings per batch
constexpr double INVALID_DATA_RATE = 0.05;   // 5% invalid data
constexpr double SENSOR_MIN = 0.0;           // Min sensor value
constexpr double SENSOR_MAX = 100.0;         // Max sensor value
constexpr double INVALID_THRESHOLD = 150.0;  // Invalid threshold
```

**Recommendations:**
- Increase `NUM_BATCHES` to see more events
- Increase `INVALID_DATA_RATE` to trigger more errors
- Adjust thresholds to change validation behavior

## Understanding the Code

### Event Logging Integration

```cpp
// Set up event logger
auto event_logger = std::make_shared<InMemoryEventLogger>(10000);
repo.SetEventLogger(event_logger);

// Later, retrieve and analyze events
auto all_events = memory_logger->GetEvents();
auto error_events = memory_logger->GetEventsByType(RuntimeEventType::ReactionFailed);
```

### Error Handling Integration

```cpp
// Configure error policy
repo.GetErrorHandler().SetPolicy(ErrorPolicy::IsolateReaction);

// Check for errors after execution
if (error_handler.HasErrors()) {
    auto failed_reactions = error_handler.GetFailedReactions();
    // Process failures...
}
```

### Lifecycle Management

```cpp
// Check runtime state
if (repo.IsRunning()) {
    // Process work...
}

// Trigger graceful shutdown
repo.Shutdown();

// Wait for completion
repo.WaitForCompletion();

// Check final state
auto state = repo.GetState();  // Should be Completed or Failed
```

### Pipeline Construction

```cpp
// Create channels for each stage
auto validator_channel = repo.NewChannel();
auto transformer_channel = repo.NewChannel();

// Register join-cases to connect stages
repo.RegisterJoinCase(
    {validator_channel},              // Input channels
    {Object::Channel(transformer_channel)},  // Context (output channel)
    1  // Runnable ID
);
```

## Observability Features

### Event Types Logged

- `ChannelCreated`: New channel allocated
- `ChannelClosed`: Channel closed
- `ReactionScheduled`: Reaction queued for execution
- `ReactionExecuted`: Reaction completed successfully
- `ReactionFailed`: Reaction threw exception
- `MessageSent`: Message pushed to channel
- `MessageReceived`: Message consumed from channel
- `LifecycleTransition`: State change (e.g., Running → ShuttingDown)

### Querying Events

```cpp
auto logger = std::dynamic_pointer_cast<InMemoryEventLogger>(repo.GetEventLogger());

// Get all events
auto all_events = logger->GetEvents();

// Get events by type
auto failures = logger->GetEventsByType(RuntimeEventType::ReactionFailed);

// Get events in time range
auto recent = logger->GetEventsInRange(start_time, end_time);

// Custom filtering
auto custom = logger->GetEventsWhere([](const RuntimeEvent& e) {
    return e.reaction_id && *e.reaction_id == 1;
});
```

## Error Policy Comparison

### FailFast
- **Behavior**: Terminates on first error
- **Use case**: Critical systems where any error is unacceptable
- **Output**: Shows first error, then exits

### IsolateReaction (Default)
- **Behavior**: Logs error, continues with other reactions
- **Use case**: Fault-tolerant systems, best-effort processing
- **Output**: Shows all errors at the end

### RetryOnce
- **Behavior**: Retries failed reaction once
- **Use case**: Transient failures (network, temporary resource issues)
- **Output**: Shows which retries succeeded/failed

### RetryWithBackoff
- **Behavior**: Retries multiple times with increasing delays
- **Use case**: Systems with intermittent failures
- **Output**: Shows retry attempts and backoff delays


## Learning Objectives

This example teaches:

1. **Event-Driven Observability**: How to instrument reactive systems
2. **Fault Tolerance**: Different strategies for handling failures
3. **Lifecycle Management**: Proper initialization and shutdown
4. **Pipeline Patterns**: Building multi-stage data flows
5. **Error Recovery**: Retry strategies and isolation
6. **System Monitoring**: Analyzing runtime behavior through events
