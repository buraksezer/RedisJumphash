# RedisJumphash

A port of [Google's "Jump" Consistent Hash function](https://arxiv.org/abs/1406.2294) as Redis module in C.

> Consistent hashing specifies a distribution of data among servers in such a way that servers can be added or 
removed without having to totally reorganize the data. It was originally proposed for web caching on the Internet, 
in order to address the problem that clients may not be aware of the entire set of cache servers.

A bit about Jump hash:

> ... jump consistent hash requires no storage, is faster, and does a better job of evenly dividing the key space among 
> the buckets and of evenly dividing the workload when the number of buckets changes.

RedisJumphash provides a very fast consistent hash function to build distributed systems with Redis.

## Usage

```
JUMPHASH <key> <number-of-buckets>
```

A successful call returns a bucket for the given key. It doesn't need any storage. If you change the number of buckets,
the algorithm guarantees minimum amount of relocation is required.

Take look at this:

```
127.0.0.1:6379> JUMPHASH buraksezer 271
(integer) 51
127.0.0.1:6379> JUMPHASH buraksezer 277
(integer) 51
```

## Rationale

It's not possible to implement this algorithm in Lua 5.1 due to lack of bitwise operators. Furthermore, Jump consistent
hash is a quite useful algorithm. As a Redis module, it would be accessible for all your clients and Lua scripts.

## Contributions

Please don't hesitate to fork the project and send a pull request or just e-mail me to ask questions and share ideas.

## License

MIT License - see LICENSE for more details.

