-- Create new channel queue
-- KEYS[1] - channel key (hash with "head", "tail")
-- KEYS[2] - first (dummy) node key

-- Initialize channel
redis.call('HSET', KEYS[1], 'head', KEYS[2])
redis.call('HSET', KEYS[1], 'tail', KEYS[2])

-- Initialize first node
redis.call('HSET', KEYS[2], 'next', '')
redis.call('HSET', KEYS[2], 'msg', '')

return true