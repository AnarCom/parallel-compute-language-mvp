-- Get from multiple channels by channel ids
--
-- Per channel:
-- KEYS[1 + i] - channel key (hash with "tail")
-- ARGV[...] - each argument is a name of a HSET field to fetch

local result = {}

for i = 1, #KEYS do
    for j = 1, #ARGV do
        local value = redis.call('HGET', KEYS[i], ARGV[j])
        table.insert(result, value)
    end
end

return result