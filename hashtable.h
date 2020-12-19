#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>
#include <fstream>
#include <string.h>

using namespace std;

template <typename K>
class Hashtable {
private:
    vector<vector<pair<K, int>>> m_map = vector<vector<pair<K, int>>>(512);
public:
    Hashtable();
    Hashtable(const Hashtable& obj);
    ~Hashtable();
    int clear();
    int size() const;
    int fromFile(const string& name);
    int toFile(const string& name) const;
    int operator==(const Hashtable& obj);
    int operator!=(const Hashtable& obj);
    void operator<<(const K& key);
    int delPlayer(const K& key);
    int inTable(const K& key) const;
    void insert(const K& key, int cnt);
    int hash(const K& key) const;
    int getScore(const K &key) const;
    int operator[](const K &key) {
        return getScore(key);
    }
    int count(int number) const;
    tuple<K, K, K> topPlayers() const;
    const vector<vector<pair<K, int>>> get() const {
        return m_map;
    }
};

template<typename K>
Hashtable<K>::Hashtable() {
    for (auto &i: this->m_map)
        for(auto &j: i)
            j.second = -1;
}

template<typename K>
Hashtable<K>::Hashtable(const Hashtable& obj) {
    for (auto &i: obj.m_map)
        for (auto &j: i)
            this->insert(j.first, j.second);
}

template<typename K>
Hashtable<K>::~Hashtable() {
    for(auto &i: this->m_map)
        i.clear();
}

template<typename K>
int Hashtable<K>::clear() {
    for (auto &i: this->m_map)
        for (auto &j: i) {
            j.first = "\0";
            j.second = -1;
        }
    return 1;
}

template<typename K>
int Hashtable<K>::size() const {
    int count = 0;

    for (auto &i: this->m_map)
        for (auto &j: i)
            if (j.second != -1)
                count++;
    return count;

}

template<typename K>
int Hashtable<K>::fromFile(const string &name) {
    string player;
    int score;
    ifstream file(name);

    if (this->size() > 0)
        this->clear();
    if (file.is_open()) {
        while (!file.eof()) {
            file >> player;
            file >> score;
            if (player != "\0" && score > 0)
                this->insert(player, score);
        }
        file.close();
    }

    return 1;
}

template<typename K>
int Hashtable<K>::toFile(const string &name) const {
    ofstream fout(name);
    //int number = 0;
    for (auto& i: this->m_map)
        for (auto& j: i) {
            if (j.first != "\0" && j.second != -1) {
                fout << j.first << endl;
                fout << j.second << "\n\n";
            }
        }
    fout.close();

    return 1;
}

template<typename K>
int Hashtable<K>::operator==(const Hashtable& obj) {
    if (this->m_map != obj.m_map)
        return 0;

    return 1;
}

template<typename K>
int Hashtable<K>::operator!=(const Hashtable& obj) {
    if (this->m_map == obj.m_map)
        return 0;

    return 1;
}

template<typename K>
void Hashtable<K>::operator<<(const K &key) {
    auto index = hash(key);
    auto& vector = this->m_map[index];
    for (auto& c: vector)
        if (c.first == key) {
            c.second++;
            return;
        }
    vector.push_back({key, 1});
}

template<typename K>
int Hashtable<K>::delPlayer(const K &key) {
    auto index = hash(key);
    auto& vector = this->m_map[index];
    int i = 0;
    for (auto& c:vector) {
        if (c.first == key)
            vector.erase(vector.begin() + i);
        i++;
    }

    return 1;
}

template<typename K>
int Hashtable<K>::inTable(const K &key) const {
    auto index = hash(key);
    auto& vector = this->m_map[index];
    for (auto& c:vector)
        if (c.first == key)
            return 1;

    return 0;
}

template<typename K>
void Hashtable<K>::insert(const K &key, int count) {
    if (count >= 0) {
        auto index = hash(key);
        auto& vector = this->m_map[index];
        for (auto& c: vector)
            if (c.first == key) {
                c.second = count;
                return;
            }
        vector.push_back({key, count});
    }
}

template<typename K>
int Hashtable<K>::hash(const K &key) const {
    int count = 0;
    for(const auto i: key)
        count += i;
    return count % 512;
}

template<typename K>
int Hashtable<K>::getScore(const K &key) const {
    auto index = hash(key);
    auto& vector = this->m_map[index];
    for (auto& c: vector)
        if (c.first == key)
            return c.second;

    return -1;
}

template<typename K>
int Hashtable<K>::count(int number) const {
    int out = 0;
    for (auto& i: this->m_map)
        for (auto& j: i)
            if (j.second >= number && j.second != -1)
                out++;

    return out;
}

template <typename K>
tuple<K, K, K> Hashtable<K>::topPlayers() const {
    string win1, win2, win3;
    int winScore1 = -1, winScore2 = -1, winScore3 = -1;
    for(auto& i: this->m_map)
            for(auto& j: i) {
                if (j.second > winScore1) {
                    win3 = win2;
                    win2 = win1;
                    winScore3 = winScore2;
                    winScore2 = winScore1;
                    win1 = j.first;
                    winScore1 = j.second;
                }
                else if (j.second > winScore2) {
                    win3 = win2;
                    win2 = j.first;
                    winScore3 = winScore2;
                    winScore2 = j.second;
                }
                else if (j.second > winScore3) {
                    win3 = j.first;
                    winScore3 = j.second;
                }
            }

    return tuple<K, K, K> (win1, win2, win3);
}

#endif // HASHTABLE_H
