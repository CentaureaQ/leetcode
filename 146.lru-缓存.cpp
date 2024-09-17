/*
 * @lc app=leetcode.cn id=146 lang=cpp
 *
 * [146] LRU 缓存
 */

// @lc code=start

#include <unordered_map>
#include <list>
#include <utility>

class LRUCache {
public:
    LRUCache(int capacity) : capacity_(capacity) {}

    int get(int key) {
        // 如果 key 不存在，返回 -1
        if (cacheMap_.find(key) == cacheMap_.end()) {
            return -1;
        }
        // 存在的话，将节点移动到链表头部
        auto it = cacheMap_[key];
        cacheList_.splice(cacheList_.begin(), cacheList_, it);
        return it->second;
    }

    void put(int key, int value) {
        // 检查 key 是否已经存在
        if (cacheMap_.find(key) != cacheMap_.end()) {
            // 如果存在，更新 value 并将节点移动到链表头部
            auto it = cacheMap_[key];
            it->second = value;
            cacheList_.splice(cacheList_.begin(), cacheList_, it);
        } else {
            // 如果缓存已满，移除链表尾部的节点
            if (cacheList_.size() == capacity_) {
                int delKey = cacheList_.back().first;
                cacheList_.pop_back();
                cacheMap_.erase(delKey);
            }
            // 插入新节点到链表头部
            cacheList_.emplace_front(key, value);
            cacheMap_[key] = cacheList_.begin();
        }
    }

private:
    int capacity_;
    std::list<std::pair<int, int>> cacheList_; // 双向链表，保存 key-value
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> cacheMap_; // 哈希表，保存 key 和链表节点的映射
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
// @lc code=end

