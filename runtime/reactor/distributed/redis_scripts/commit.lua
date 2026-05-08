-- Receive execution result and push it to channels
-- KEYS:
-- KEYS[1] - expected head node key (exec queue)
-- KEYS[2] - exec queue key (hash with 'head')
--
-- Per output channel (n = ARGV[1]):
-- KEYS[3 + i*2]     - expected tail node key
-- KEYS[3 + i*2 + 1] - channel key (hash with 'tail')
--
-- Per msg:
-- KEYS[3 + n*2 + 1 + i] - new node key
--
-- ARGV:
-- ARGV[1] - number of output channels (n)
-- ARGV[2 + i] - new msg for channel i

local n = tonumber(ARGV[1]) -- 1

-- Validate exec queue head
local real_head = redis.call('HGET', KEYS[2], 'head')
if real_head ~= KEYS[1] then
    return false
end

-- Validate all channel tails first
for i = 0, n - 1 do
    local expected_tail = KEYS[3 + i * 2]
    local channel = KEYS[3 + i * 2 + 1]

    local real_tail = redis.call('HGET', channel, 'tail')
    if real_tail ~= expected_tail then
        return false
    end
end

-- Advance exec queue head
local next_head = redis.call('HGET', KEYS[1], 'next')
redis.call('HSET', KEYS[2], 'head', next_head)

-- Push results into each channel
for i = 0, n - 1 do
    local expected_tail = KEYS[3 + i * 2]
    local channel = KEYS[3 + i * 2 + 1]

    local new_node = KEYS[3 + n * 2 + i]
    local msg = ARGV[2 + i]

    -- Same pattern as your push script
    redis.call('HSET', expected_tail, 'next', new_node)
    redis.call('HSET', expected_tail, 'msg', msg)
    redis.call('HSET', channel, 'tail', new_node)
    redis.call('HSET', new_node, 'next', '')
    redis.call('HSET', new_node, 'msg', '')
end

return true