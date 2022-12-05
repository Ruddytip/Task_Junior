#pragma once
#include "task.hpp"
#include <vector>

// Класс исключений
template<class Key>
class Ex : public not_found_exception<Key>{
private:
    Key key;
public:
    Ex(const Key& _key): key(_key){}
    const Key& get_key() const noexcept { return key; }
};
// Возможно я не правильно понял, может Вы имели ввиду, что класс not_found_exception
// должен вызывать исключение при отсутствии исключений при работе класса Container

template<typename Key, typename Value>
class Container: public dictionary<Key, Value>{
private:
    // Вспомогательная структура для хранения пар ключ-значение в векторе
    struct Node{
        Key key;
        Value value;
        Node(const Key& _key, const Value& _value): key(_key), value(_value){}
    };
    std::vector<Node> data;
public:
    Container(){ data.clear(); }
    ~Container(){ data.clear(); }

    // Получает значение value с ключём key, если указанного ключа нет, то бросает исключение
    const Value& get(const Key& key) const {
        if(data.empty() || !is_set(key)) throw Ex<Key>(key);
        for(auto& it : data) if(it.key == key) return it.value;
        throw Ex<Key>(key);
    }

    // Добавляет в контейнер пару ключ-значение, но если в контейнере уже есть указанный ключ, то бросает исключение
    void set(const Key& key, const Value& value){
        if(!is_set(key)){
            data.push_back(Node(key, value));
        }else{
            throw Ex<Key>(key);
        }
    }

    // Проверка нахождения ключа в контейнере
    bool is_set(const Key& key) const {
        for(auto& it : data) if(it.key == key) return true;
        return false;
    }
};