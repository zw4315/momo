// test_tag_registry.cpp
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <thread>

// === 临时打桩接口（真实实现还没写） ===
class TagRepository {
 public:
  virtual ~TagRepository() = default;
  virtual std::vector<std::pair<int, std::string>> LoadAllTags() = 0;
};

class TagRegistry {
 public:
  void LoadFromRepository(TagRepository& repo) {
    auto tags = repo.LoadAllTags();
    for (auto& [id, name] : tags) {
      id_to_name_[id] = name;
    }
  }

  int FindOrRegister(const std::string& name) {
    std::lock_guard<std::mutex> lock(mu_);
    for (auto& [id, nm] : id_to_name_) {
      if (nm == name) return id;
    }
    int new_id = static_cast<int>(id_to_name_.size() + 1);
    id_to_name_[new_id] = name;
    return new_id;
  }

  std::string GetName(int id) const {
    auto it = id_to_name_.find(id);
    return (it != id_to_name_.end()) ? it->second : "";
  }

  int GetCount() const { return static_cast<int>(id_to_name_.size()); }

 private:
  std::unordered_map<int, std::string> id_to_name_;
  mutable std::mutex mu_;
};

using namespace testing;

// ===== Mock 类 =====
class MockTagRepository : public TagRepository {
 public:
  // mock 所有纯虚函数
  MOCK_METHOD((std::vector<std::pair<int, std::string>>), LoadAllTags, (),
              (override));
  // 如果 TagRepository 还有别的纯虚函数，比如 SaveTag / DeleteTag 等，也要加
};

// ===== 测试 Fixture =====
class TagRegistryTest : public ::testing::Test {
 protected:
  MockTagRepository mock_repo;
};

// 测试 1：启动时加载已有标签
TEST_F(TagRegistryTest, LoadExistingTagsOnStartup) {
  TagRegistry registry;

  // 模拟数据库返回已有标签
  std::vector<std::pair<int, std::string>> existing = {{1, "work"},
                                                       {2, "personal"}};

  EXPECT_CALL(mock_repo, LoadAllTags()).WillOnce(Return(existing));

  registry.LoadFromRepository(mock_repo);

  EXPECT_EQ(registry.GetCount(), 2);
  EXPECT_EQ(registry.GetName(1), "work");
  EXPECT_EQ(registry.GetName(2), "personal");
}

// 测试 2：找不到标签时自动分配 ID
TEST_F(TagRegistryTest, FindOrRegisterCreatesNewIdAndPersists) {
  TagRegistry registry;

  EXPECT_CALL(mock_repo, LoadAllTags())
      .WillOnce(Return(std::vector<std::pair<int, std::string>>{}));

  registry.LoadFromRepository(mock_repo);

  int id = registry.FindOrRegister("urgent");
  EXPECT_EQ(registry.GetName(id), "urgent");
}

// 测试 3：并发安全性（简单并发模拟）
TEST_F(TagRegistryTest, ThreadSafeConcurrentRegisterSameTagGetsSameId) {
  TagRegistry registry;

  EXPECT_CALL(mock_repo, LoadAllTags())
      .WillOnce(Return(std::vector<std::pair<int, std::string>>{}));

  registry.LoadFromRepository(mock_repo);

  auto worker = [&registry]() { return registry.FindOrRegister("shared_tag"); };

  int id1, id2;
  std::thread t1([&]() { id1 = worker(); });
  std::thread t2([&]() { id2 = worker(); });

  t1.join();
  t2.join();

  EXPECT_EQ(id1, id2);
}
