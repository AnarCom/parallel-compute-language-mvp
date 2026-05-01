-- Pull msgs from channels and enqueue for execution
-- KEYS:
-- KEYS[1] - expected tail (exec queue)
-- KEYS[2] - new tail (exec queue)
-- KEYS[3] - exec queue key (hash with 'tail')
-- KEYS[4...] - per input channel:
--   KEYS[4 + i*2]     - expected head node key
--   KEYS[4 + i*2 + 1] - channel key (hash with 'head')

local exec_tail = redis.call('HGET', KEYS[3], 'tail')

-- Check exec queue tail consistency
if exec_tail ~= KEYS[1] then
    return {}
end

local result = {}
local pulled_heads = {}

-- First pass: validate all channels
local num_channels = (#KEYS - 3) / 2

for i = 0, num_channels - 1 do
    local expected_head = KEYS[4 + i * 2]
    local channel = KEYS[4 + i * 2 + 1]

    local real_head = redis.call('HGET', channel, 'head')
    if real_head ~= expected_head then
        return {}
    end

    local msg = redis.call('HGET', expected_head, 'msg')
    if not msg or msg == '' then
        return {}
    end

    table.insert(result, msg)
    table.insert(pulled_heads, expected_head)
end

-- Second pass: advance heads
for i = 0, num_channels - 1 do
    local expected_head = KEYS[4 + i * 2]
    local channel = KEYS[4 + i * 2 + 1]

    local next_head = redis.call('HGET', expected_head, 'next')
    redis.call('HSET', channel, 'head', next_head)
end

-- Append to execution queue (same pattern as your push script)
redis.call('HSET', KEYS[1], 'next', KEYS[2])
redis.call('HSET', KEYS[1], 'msgs', table.concat(pulled_heads, ','))
redis.call('HSET', KEYS[3], 'tail', KEYS[2])
redis.call('HSET', KEYS[2], 'next', '')

return result