
#include "infrastructure/persistence/file/FileTagRepository.h"
#include <filesystem>
#include <sstream>
#include <algorithm>

namespace fs = std::filesystem;
namespace momo::infra {
using momo::domain::Tag;

FileTagRepository::FileTagRepository(std::string path) : path_(std::move(path)) {
  ensureFile(); computeNextId();
}
FileTagRepository::~FileTagRepository() = default;

void FileTagRepository::ensureFile() { if (!fs::exists(path_)) { std::ofstream ofs(path_); ofs << ""; } }
void FileTagRepository::computeNextId() {
  std::ifstream ifs(path_); std::string line; int maxId = 0;
  while (std::getline(ifs, line)) if (auto p = parseLine(line)) maxId = std::max(maxId, p->first);
  next_id_ = maxId + 1;
}
std::optional<std::pair<int,std::string>> FileTagRepository::parseLine(const std::string& line) {
  if (line.empty()) return std::nullopt;
  std::istringstream iss(line); std::string idStr, name;
  if (!std::getline(iss, idStr, ',')) return std::nullopt;
  if (!std::getline(iss, name)) return std::nullopt;
  try { return std::make_pair(std::stoi(idStr), name); } catch (...) { return std::nullopt; }
}
std::vector<Tag> FileTagRepository::LoadAllTags() {
  std::vector<Tag> out; std::ifstream ifs(path_); std::string line;
  while (std::getline(ifs, line)) if (auto p = parseLine(line)) out.push_back(Tag{p->first, p->second});
  return out;
}
Tag FileTagRepository::SaveTag(const Tag& tag) {
  int id = tag.id != 0 ? tag.id : next_id_++;
  std::ofstream ofs(path_, std::ios::app); ofs << id << "," << tag.name << "\n";
  return Tag{id, tag.name};
}
void FileTagRepository::SaveAll(const std::vector<Tag>& tags) {
  std::ofstream ofs(path_, std::ios::trunc);
  for (const auto& t : tags) ofs << t.id << "," << t.name << "\n";
  computeNextId();
}
} // namespace momo::infra
