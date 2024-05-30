#ifndef LINQCPP_H
#define LINQCPP_H

#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <map>
using namespace std;

// Методы для работы с последовательностями, имитирующие LINQ-запросы.

/// Фильтрует элементы последовательности согласно условию.
template <typename Container, typename Condition>
auto Where(const Container& container, Condition condition);

/// Применяет функцию к каждому элементу последовательности, возвращая новую последовательность.
template<typename Container, typename Selector>
auto Select(const Container& container, Selector selector);

/// Сортирует элементы последовательности по заданному компаратору.
template<typename Container, typename Comparator>
auto OrderBy(const Container& container, Comparator comparator);

/// Дополнительная сортировка элементов последовательности после применения OrderBy.
/// Более приоритетные ключи должны быть указаны в последнюю очередь.
template<typename Container, typename Comparator>
auto ThenBy(const Container& container, Comparator comparator);

/// Группирует элементы последовательности по ключу, возвращая вектор пар ключ-группа.
template<typename Container, typename KeySelector>
auto GroupBy(const Container& container, KeySelector keySelector);

/// Возвращает новую последовательность с заданным количеством элементов из начала исходной.
template<typename Container>
auto Take(const Container& container, size_t count);

/// Объединяет две последовательности поэлементно с помощью заданной функции.
template<typename Container1, typename Container2, typename ResultSelector>
auto Zip(const Container1& container1, const Container2& container2, ResultSelector selector);

/// Применяет функцию к каждому элементу последовательности и "выпрямляет" результат в одну последовательность.
template<typename Container, typename Selector>
auto SelectMany(const Container& container, Selector selector);

/// Применяет действие к каждому элементу последовательности.
template<typename Container, typename Action>
auto ForEach(const Container& container, Action action);

/// Возвращает последовательность с одним элементом, если исходная последовательность пуста.
template<typename Container>
auto DefaultIfEmpty(const Container& container);

/// Возвращает последовательность с одним элементом, если исходная последовательность пуста.
template<typename Container>
auto DefaultIfEmpty(const Container& container, typename Container::value_type default_value);

/// Возвращает первый элемент последовательности или значение по умолчанию, если последовательность пуста.
template<typename Container>
auto FirstOrDefault(const Container& container);

/// Возвращает новую последовательность, состоящую из результатов соединения элементов двух коллекций по заданным ключам.
template<typename Container1, typename Container2, typename KeySelector1, typename KeySelector2, typename ResultSelector>
auto Join(const Container1& container1, const Container2& container2,
          KeySelector1 keySelector1, KeySelector2 keySelector2,
          ResultSelector resultSelector);

/// Соединяет две последовательности в одну и выполняет группировку.
template<typename Container1, typename Container2, typename KeySelector1, typename KeySelector2, typename ResultSelector>
auto GroupJoin(const Container1& container1, const Container2& container2,
               KeySelector1 keySelector1, KeySelector2 keySelector2,
               ResultSelector resultSelector);

/// Размещает элементы исходной последовательности в обратном порядке
template <typename Container>
auto Reverse(const Container& container);

/// Вычисляет среднее значение элементов в последовательности.
template <typename Container>
double Average(const Container& numbers);

/// Вычисляет сумму всех элементов в последовательности.
template <typename Container>
typename Container::value_type Sum(const Container& numbers);

/// Проверяет, удовлетворяют ли все элементы последовательности заданному условию.
template<typename Container, typename Condition>
bool All(const Container& container, Condition condition);

/// Проверяет, удовлетворяет ли хотя бы один элемент последовательности заданному условию.
template<typename Container, typename Condition>
bool Any(const Container& container, Condition condition);

/// Находит минимальный элемент в последовательности.
template<typename Container>
auto Min(const Container& container);

/// Находит максимальный элемент в последовательности.
template<typename Container>
auto Max(const Container& container);

/// Класс-обертка над вектором для работы с LINQ-запросами
template <typename T>
class Seq {
private:
    vector<T> container;

public:
    explicit Seq(const vector<T>& data) : container(data) {}

    using iterator = typename vector<T>::iterator;
    using const_iterator = typename vector<T>::const_iterator;
    using reverse_iterator = typename std::vector<T>::reverse_iterator;
    using const_reverse_iterator = typename std::vector<T>::const_reverse_iterator;
    using value_type = T;

    iterator begin() { return container.begin(); }
    iterator end() { return container.end(); }
    const_iterator begin() const { return container.begin(); }
    const_iterator end() const { return container.end(); }

    reverse_iterator rbegin() { return container.rbegin(); }
    reverse_iterator rend() { return container.rend(); }
    const_reverse_iterator rbegin() const { return container.rbegin(); }
    const_reverse_iterator rend() const { return container.rend(); }

    operator vector<T>() const { return container; }

    size_t size() const { return container.size(); }
    bool empty() const { return container.empty(); }

    void push_back(const T& value) { container.push_back(value); }
    void pop_back() { container.pop_back(); }

    T& operator[](size_t index) { return container[index]; }
    const T& operator[](size_t index) const { return container[index]; }
    T& front() { return container.front(); }
    const T& front() const { return container.front(); }
    T& back() { return container.back(); }
    const T& back() const { return container.back(); }

    iterator find(const T& value) {
        return std::find(container.begin(), container.end(), value);
    }

    /// Фильтрует элементы последовательности согласно условию.
    template <typename Condition>
    auto Where(Condition condition) const { return ::Where(container, condition); }

    /// Применяет функцию к каждому элементу последовательности, возвращая новую последовательность.
    template<typename Selector>
    auto Select(Selector selector) const { return ::Select(container, selector); }

    /// Сортирует элементы последовательности по заданному компаратору.
    template<typename Comparator>
    auto OrderBy(Comparator comparator) const { return ::OrderBy(container, comparator); }

    /// Дополнительная сортировка элементов последовательности после применения OrderBy.
    /// Более приоритетные ключи должны быть указаны в последнюю очередь.
    template<typename Comparator>
    auto ThenBy(Comparator comparator) const { return ::ThenBy(container, comparator); }

	/// Группирует элементы последовательности по ключу, возвращая вектор пар ключ-группа.
    template<typename KeySelector>
    auto GroupBy(KeySelector keySelector) const { return ::GroupBy(container, keySelector); }

    /// Возвращает новую последовательность с заданным количеством элементов из начала исходной.
    auto Take(size_t count) const { return ::Take(container, count); }

    /// Объединяет две последовательности поэлементно с помощью заданной функции.
    template<typename Container2, typename ResultSelector>
    auto Zip(const vector<Container2>& container2, ResultSelector selector) const {
        return ::Zip(container, container2, selector);
    }

    /// Применяет функцию к каждому элементу последовательности и "выпрямляет" результат в одну последовательность.
    template<typename Selector>
    auto SelectMany(Selector selector) const { return ::SelectMany(container, selector); }

	/// Применяет действие к каждому элементу последовательности.
	template<typename Action>
	auto ForEach(Action action) const { return ::ForEach(container, action); }

	/// Возвращает последовательность с одним элементом, если исходная последовательность пуста.
	auto DefaultIfEmpty() const { return ::DefaultIfEmpty(container); }

    	/// Возвращает последовательность с одним элементом, если исходная последовательность пуста.
	auto DefaultIfEmpty(T default_value) const { return ::DefaultIfEmpty(container, default_value); }
    
    /// Возвращает первый элемент последовательности или значение по умолчанию, если последовательность пуста.
    auto FirstOrDefault() const { return ::FirstOrDefault(container); }

	/// Возвращает новую последовательность, состоящую из результатов соединения элементов двух коллекций по заданным ключам.
	template<typename Container2, typename KeySelector1, typename KeySelector2, typename ResultSelector>
	auto Join(const Container2& container2,
			KeySelector1 keySelector1, KeySelector2 keySelector2,
			ResultSelector resultSelector) const {
		return ::Join(container, container2, keySelector1, keySelector2, resultSelector);
	}

	/// Соединяет две последовательности в одну и выполняет группировку.
	template<typename Container2, typename KeySelector1, typename KeySelector2, typename ResultSelector>
	auto GroupJoin(const Container2& container2,
			KeySelector1 keySelector1, KeySelector2 keySelector2,
			ResultSelector resultSelector) const {
		return ::GroupJoin(container, container2, keySelector1, keySelector2, resultSelector);
	}

    /// Размещает элементы исходной последовательности в обратном порядке
    template <typename Container>
    auto Reverse() const {
        return ::Reverse(container);
    }

    /// Вычисляет среднее значение элементов в последовательности.
    double Average() const { return ::Average(container); }

    /// Вычисляет сумму всех элементов в последовательности.
    T Sum() const { return ::Sum(container); }

    /// Проверяет, удовлетворяют ли все элементы последовательности заданному условию.
    template<typename Condition>
    bool All(Condition condition) const { return ::All(container, condition); }

    /// Проверяет, удовлетворяет ли хотя бы один элемент последовательности заданному условию.
    template<typename Condition>
    bool Any(Condition condition) const { return ::Any(container, condition); }

    /// Находит минимальный элемент в последовательности.
    T Min() const { return ::Min(container); }

    /// Находит максимальный элемент в последовательности.
    T Max() const { return ::Max(container); }
};

/// Возвращает последовательность на основе вектора data
template<typename T>
Seq<T> make_seq(const vector<T>& data) {
    return Seq<T>(data);
}

/// Фильтрует элементы последовательности согласно условию.
template <typename Container, typename Predicate>
auto Where(const Container& container, Predicate predicate) {
    using T = typename Container::value_type;
    vector<T> result;
    copy_if(container.begin(), container.end(), back_inserter(result), predicate);
    return Seq<T>(result);
}

/// Применяет функцию к каждому элементу последовательности, возвращая новую последовательность.
template<typename Container, typename Selector>
auto Select(const Container& container, Selector selector) {
    using TResult = decltype(selector(*container.begin()));
    vector<TResult> result;
    transform(container.begin(), container.end(), back_inserter(result), selector);
    return Seq<TResult>(result);
}

/// Сортирует элементы последовательности по заданному компаратору.
template<typename Container, typename Comparator>
auto OrderBy(const Container& container, Comparator comparator) {
    using T = typename Container::value_type;
    vector<T> sorted(container.begin(), container.end());
    stable_sort(sorted.begin(), sorted.end(), comparator);
    return Seq<T>(sorted);
}

/// Дополнительная сортировка элементов последовательности после применения OrderBy.
/// Более приоритетные ключи должны быть указаны в последнюю очередь.
template<typename Container, typename Comparator>
auto ThenBy(const Container& container, Comparator comparator) {
    using T = typename Container::value_type;
    vector<T> sorted(container);
    stable_sort(sorted.begin(), sorted.end(), comparator);
    return Seq<T>(sorted);
}

/// Группирует элементы последовательности по ключу, возвращая вектор пар ключ-группа.
template<typename Container, typename KeySelector>
auto GroupBy(const Container& container, KeySelector keySelector) {
    using T = typename Container::value_type;
    using KeyType = decltype(keySelector(*container.begin()));

    map<KeyType, vector<T>> groups;
    for (const auto& elem : container) {
        KeyType key = keySelector(elem);
        groups[key].push_back(elem);
    }

    vector<pair<KeyType, vector<T>>> result;
    for (auto elem : container) {
        KeyType key = keySelector(elem);
        if ( groups.find(key) != groups.end()) {
            result.push_back(make_pair(key, groups[key]));
            groups.erase(key);
            if (groups.size() == 0)
                break;
        }
    }

    return Seq<pair<KeyType, vector<T>>>(result);
}

/// Возвращает новую последовательность с заданным количеством элементов из начала исходной.
template<typename Container>
auto Take(const Container& container, size_t count) {
    using T = typename Container::value_type;
    vector<T> result;
    size_t taken = 0;
    for (const auto& elem : container) {
        if (taken >= count)
            break;
        result.push_back(elem);
        ++taken;
    }
    return Seq<T>(result);
}

/// Объединяет две последовательности поэлементно с помощью заданной функции.
template<typename Container1, typename Container2, typename ResultSelector>
auto Zip(const Container1& container1, const Container2& container2, ResultSelector selector) {
    using TResult = decltype(selector(*container1.begin(), *container2.begin()));
    vector<TResult> result;
    auto iter1 = container1.begin();
    auto iter2 = container2.begin();
    while (iter1 != container1.end() && iter2 != container2.end()) {
        result.push_back(selector(*iter1, *iter2));
        ++iter1;
        ++iter2;
    }
    return Seq<TResult>(result);
}

/// Применяет функцию к каждому элементу последовательности и "выпрямляет" результат в одну последовательность.
template<typename Container, typename Selector>
auto SelectMany(const Container& container, Selector selector) {
    using T = typename Container::value_type;
    using InnerContainer = typename result_of<Selector(T)>::type;
    vector<typename InnerContainer::value_type> result;
    for (const auto& elem : container) {
        auto innerContainer = selector(elem);
        result.insert(result.end(), innerContainer.begin(), innerContainer.end());
    }
    return Seq<typename InnerContainer::value_type>(result);
}

/// Применяет действие к каждому элементу последовательности.
template<typename Container, typename Action>
auto ForEach(const Container& container, Action action) {
    using T = typename Container::value_type;
    for_each(container.begin(), container.end(), action);
    return Seq<T>(container);
}

/// Возвращает последовательность с одним элементом, если исходная последовательность пуста.
template<typename Container>
auto DefaultIfEmpty(const Container& container) {
	using T = typename Container::value_type;
    return container.empty() ? Seq<T>({T{}}) : Seq<T>(container);
}

/// Возвращает последовательность с одним элементом, если исходная последовательность пуста.
template<typename Container>
auto DefaultIfEmpty(const Container& container, typename Container::value_type default_value) {
	using T = typename Container::value_type;
    return container.empty() ? Seq<T>({default_value}) : Seq<T>(container);
}

/// Возвращает первый элемент последовательности или значение по умолчанию, если последовательность пуста.
template<typename Container>
auto FirstOrDefault(const Container& container) {
	using T = typename Container::value_type;
    return container.empty() ? T{} : *container.begin();
}

/// Возвращает новую последовательность, состоящую из результатов соединения элементов двух коллекций по заданным ключам.
template<typename Container1, typename Container2, typename KeySelector1, typename KeySelector2, typename ResultSelector>
auto Join(const Container1& container1, const Container2& container2, KeySelector1 keySelector1, KeySelector2 keySelector2, ResultSelector resultSelector) {
    using T1 = typename Container1::value_type;
    using T2 = typename Container2::value_type;
    using KeyType1 = decltype(keySelector1(*container1.begin()));
    using KeyType2 = decltype(keySelector2(*container2.begin()));

    map<KeyType1, vector<T1>> group1;
    for (const auto& elem : container1) {
        KeyType1 key = keySelector1(elem);
        group1[key].push_back(elem);
    }

    map<KeyType2, vector<T2>> group2;
    for (const auto& elem : container2) {
        KeyType2 key = keySelector2(elem);
        group2[key].push_back(elem);
    }

    vector<decltype(resultSelector(*container1.begin(), *container2.begin()))> result;

    for (const auto& pair1 : group1) {
        auto key = pair1.first;
        if (group2.find(key) != group2.end()) {
            const auto& group1_elements = pair1.second;
            const auto& group2_elements = group2[key];
            for (const auto& elem1 : group1_elements) {
                for (const auto& elem2 : group2_elements) {
                    result.push_back(resultSelector(elem1, elem2));
                }
            }
        }
    }

    return Seq<decltype(resultSelector(*container1.begin(), *container2.begin()))>(result);
}

/// Соединяет две последовательности в одну и выполняет группировку.
template<typename Container1, typename Container2, typename KeySelector1, typename KeySelector2, typename ResultSelector>
auto GroupJoin(const Container1& container1, const Container2& container2, KeySelector1 keySelector1, KeySelector2 keySelector2, ResultSelector resultSelector) {
    using T2 = typename Container2::value_type;
    using KeyType1 = decltype(keySelector1(*container1.begin()));
    using KeyType2 = decltype(keySelector2(*container2.begin()));

    map<KeyType2, vector<T2>> group2;
    for (const auto& elem : container2) {
        KeyType2 key = keySelector2(elem);
        group2[key].push_back(elem);
    }

    vector<decltype(resultSelector(*container1.begin(), vector<T2>{}))> result;

    for (const auto& elem1 : container1) {
        KeyType1 key = keySelector1(elem1);
        if (group2.find(key) != group2.end()) {
            const auto& group2_elements = group2[key];
            result.push_back(resultSelector(elem1, group2_elements));
        } else {
            result.push_back(resultSelector(elem1, vector<T2>{}));
        }
    }

    return Seq<decltype(resultSelector(*container1.begin(), vector<T2>{}))>(result);
}

/// Размещает элементы исходной последовательности в обратном порядке
template <typename Container>
auto Reverse(const Container& container) {
    using T = typename Container::value_type;
    auto result = Seq<T>(container);
    reverse(result.begin(), result.end());
    return result;
}

/// Вычисляет среднее значение элементов в последовательности.
template <typename Container>
double Average(const Container& numbers) {
    if (numbers.empty()) {
        return 0.0;
    }
    typename Container::value_type sum = accumulate(numbers.begin(), numbers.end(), typename Container::value_type{});
    return static_cast<double>(sum) / numbers.size();
}

/// Вычисляет сумму всех элементов в последовательности.
template <typename Container>
typename Container::value_type Sum(const Container& numbers) {
    if (numbers.empty()) {
        return typename Container::value_type{};
    }
    return accumulate(numbers.begin(), numbers.end(), typename Container::value_type{});
}

/// Проверяет, удовлетворяют ли все элементы последовательности заданному условию.
template<typename Container, typename Predicate>
bool All(const Container& container, Predicate predicate) {
    return all_of(container.begin(), container.end(), predicate);
}

/// Проверяет, удовлетворяет ли хотя бы один элемент последовательности заданному условию.
template<typename Container, typename Predicate>
bool Any(const Container& container, Predicate predicate) {
    return any_of(container.begin(), container.end(), predicate);
}

/// Находит минимальный элемент в последовательности.
template<typename Container>
auto Min(const Container& container) {
    return container.empty() ? typename Container::value_type{} : *min_element(container.begin(), container.end());
}

/// Находит максимальный элемент в последовательности.
template<typename Container>
auto Max(const Container& container) {
    return container.empty() ? typename Container::value_type{} : *max_element(container.begin(), container.end());
}

#endif //LINQCPP_H