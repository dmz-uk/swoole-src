/*
  +----------------------------------------------------------------------+
  | Open Swoole                                                          |
  +----------------------------------------------------------------------+
  | This source file is subject to version 2.0 of the Apache license,    |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.apache.org/licenses/LICENSE-2.0.html                      |
  | If you did not receive a copy of the Apache2.0 license and are unable|
  | to obtain it through the world-wide-web, please send a note to       |
  | hello@swoole.co.uk so we can mail you a copy immediately.            |
  +----------------------------------------------------------------------+
  | @author   Tianfeng Han  <mikan.tenny@gmail.com>                      |
  +----------------------------------------------------------------------+
*/

#include "test_core.h"
#include "swoole_memory.h"

using namespace std;

TEST(fixed_pool, alloc) {
    auto *pool = new swoole::FixedPool(1024, 256, false);

    list<void *> alloc_list;

    for (int i = 0; i < 1200; i++) {
        int j = rand();
        if (j % 4 < 3) {
            void *mem = pool->alloc(0);
            ASSERT_TRUE(mem);
            alloc_list.push_back(mem);
        } else if (!alloc_list.empty()) {
            void *mem = alloc_list.front();
            pool->free(mem);
        }
    }

    delete pool;
}
