#include <ctype.h>
#include <stdlib.h>
#include <xxhash.h>
#include "redismodule.h"

int32_t JumpConsistentHash(uint64_t key, int32_t num_buckets) {
    int64_t b = -1, j = 0;
    while (j < num_buckets) {
        b = j;
        key = key * 2862933555777941757ULL + 1;
        j = (double)(b + 1) * ((double)(1LL << 31) / (double)((key >> 33) + 1));
    }
    return b;
}

int Jumphash_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (argc != 3) { // Enforce 2 args
        return RedisModule_WrongArity(ctx);
    }
    RedisModule_AutoMemory(ctx); /* Use automatic memory management. */

    RedisModuleString *key = argv[1];
    RedisModuleString *numBuckets = argv[2];

    size_t key_len;
    const char *str_key = RedisModule_StringPtrLen(key, &key_len);

    XXH64_hash_t  const hash = XXH64(str_key, key_len, 0);

    size_t len_num_buckets;
    const char *str_num_buckets = RedisModule_StringPtrLen(numBuckets, &len_num_buckets);
    unsigned long long nm = strtoull(str_num_buckets, NULL, 10);

    int32_t bucket = JumpConsistentHash((uint64_t)hash, (int32_t)nm);
    return RedisModule_ReplyWithLongLong(ctx, (long)(bucket));
}

int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (RedisModule_Init(ctx,"Jumphash",1, REDISMODULE_APIVER_1) == REDISMODULE_ERR) {
        return REDISMODULE_ERR;
    }

    if (RedisModule_CreateCommand(ctx, "Jumphash", Jumphash_RedisCommand, "readonly", 1, 1, 1) == REDISMODULE_ERR) {
        return REDISMODULE_ERR;
    }

    return REDISMODULE_OK;
}