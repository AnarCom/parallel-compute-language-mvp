-- Send msg to channel
-- 3 keys & 1 args
-- KEYS[1] - expected tail
-- KEYS[2] - new tail
-- KEYS[3] - channel
-- ARGV[1] - new msg

local real_tail = redis.call('HGET', KEYS[3], 'tail')
if real_tail == KEYS[1] then
    redis.call('HSET', KEYS[1], 'next', KEYS[2])
    redis.call('HSET', KEYS[1], 'msg', ARGV[1])
    redis.call('HSET', KEYS[3], 'tail', KEYS[2])
    redis.call('HSET', KEYS[2], 'next', '')
    redis.call('HSET', KEYS[2], 'msg', '')
    return true
else
    return false
end
