# RedisJumphash

A port of [Google's "Jump" Consistent Hash function](https://arxiv.org/abs/1406.2294) as Redis module in C.

> Consistent hashing specifies a distribution of data among servers in such a way that servers can be added or 
removed without having to totally reorganize the data. It was originally proposed for web caching on the Internet, 
in order to address the problem that clients may not be aware of the entire set of cache servers.

RedisJumphash provides a very fast Consistent Hash function to build distributed systems with Redis.

## Usage

```
JUMPHASH <key> <number-of-buckets>
```

A successful call returns a bucket for the given key.

## Contributions

Please don't hesitate to fork the project and send a pull request or just e-mail me to ask questions and share ideas.

## License

MIT License - see LICENSE for more details.

