#ifndef EVENT_H
#define EVENT_H

#include <memory>
#include <set>
#include <string>

enum class EventStatus { kTodo, kDoing, kDone };

class Event {
 public:
  Event(const std::string& title, const std::string& description = "");

 private:
  int id_;
  int priority_;
  EventStatus status_;
  std::string title_;
  std::string description_;
  std::string created_at_;
  std::string updated_at_;
  std::string due_at_;
  std::vector<std::string> tags_;  // 用于展示/传输
  std::unordered_map<std::string, float> metrics_;
};

#endif  // EVENT_H
