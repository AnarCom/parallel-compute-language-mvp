-- Create new execution queue
-- KEYS[1] - exec queue key (hash with "head", "tail")
-- KEYS[2] - first (dummy) node key

-- Initialize exec queue
redis.call('HSET', KEYS[1], 'head', KEYS[2])
redis.call('HSET', KEYS[1], 'tail', KEYS[2])

-- Initialize first node
redis.call('HSET', KEYS[2], 'next', '')
redis.call('HSET', KEYS[2], 'msgs', '')

return true