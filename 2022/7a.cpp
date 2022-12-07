#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

class Directory {
   public:
    Directory(const auto& name);
    [[nodiscard]] auto getSize() const -> ll;
    [[nodiscard]] auto getName() const -> string;
    [[nodiscard]] auto getSubDirectories() const
        -> vector<shared_ptr<Directory>>;
    auto addFile(const auto& fileSize) -> void;
    auto addSubDirectory(const auto& directory) -> shared_ptr<Directory>;

   private:
    ll size;
    const string name;
    vector<shared_ptr<Directory>> subDirectories;
};

Directory::Directory(const auto& name) : size(0), name(name) {}

[[nodiscard]] auto Directory::getSize() const -> ll { return size; }

[[nodiscard]] auto Directory::getName() const -> string { return name; }

[[nodiscard]] auto Directory::getSubDirectories() const
    -> vector<shared_ptr<Directory>> {
    return subDirectories;
}

auto Directory::addFile(const auto& fileSize) -> void { size += fileSize; }

auto Directory::addSubDirectory(const auto& directory)
    -> shared_ptr<Directory> {
    for (const auto& subDirectory : subDirectories) {
        if (subDirectory->getName() == directory->getName()) {
            return subDirectory;
        }
    }
    subDirectories.push_back(directory);
    return directory;
}

class FileSystem {
   public:
    FileSystem(const auto& input);
    auto getDirectories() -> vector<shared_ptr<Directory>>;

   private:
    shared_ptr<Directory> root;
};

FileSystem::FileSystem(const auto& input) {
    root = make_shared<Directory>(".");
    auto path = vector<shared_ptr<Directory>>{root};
    for (const auto& line : input) {
        if (auto match = smatch{};
            regex_match(line, match, regex("^\\$ cd (.*)$"))) {
            if (match.str(1) == "..") {
                path.pop_back();
            } else {
                auto newDirectory = path.back()->addSubDirectory(
                    make_shared<Directory>(match.str(1)));
                path.push_back(newDirectory);
            }
        } else if (regex_match(line, match, regex("^dir (.*)$"))) {
            path.back()->addSubDirectory(make_shared<Directory>(match.str(1)));
        } else if (regex_match(line, match, regex("^(\\d+) .*$"))) {
            path.back()->addFile(stoll(match.str(1)));
        }
    }

    auto seen = unordered_set<shared_ptr<Directory>>{};
    auto dfs = [&](auto&& dfs, const auto& dir) -> void {
        if (seen.contains(dir)) return;
        seen.insert(dir);
        for (const auto& subDir : dir->getSubDirectories()) {
            dfs(dfs, subDir);
            dir->addFile(subDir->getSize());
        }
    };
    dfs(dfs, path.front());
}

[[nodiscard]] auto FileSystem::getDirectories()
    -> vector<shared_ptr<Directory>> {
    auto seen = unordered_set<shared_ptr<Directory>>{};
    auto dfs = [&](auto&& dfs, const auto& dir) -> void {
        if (seen.contains(dir)) return;
        seen.insert(dir);
        for (const auto& subDir : dir->getSubDirectories()) {
            dfs(dfs, subDir);
        }
    };
    dfs(dfs, root);

    auto directories = vector<shared_ptr<Directory>>{};
    directories.reserve(seen.size());
    for (const auto& directory : seen) {
        directories.push_back(directory);
    }
    return directories;
}

auto main() -> int {
    auto lines = vector<string>{};
    for (auto line = string{}; getline(cin, line);) {
        lines.push_back(line);
    }

    constexpr auto MAX_SIZE = ll{100'000};
    auto sum = ll{};
    auto fs = FileSystem(lines);
    for (const auto& directory : fs.getDirectories()) {
        if (directory->getSize() <= MAX_SIZE) {
            sum += directory->getSize();
        }
    }
    cout << sum << endl;
}
