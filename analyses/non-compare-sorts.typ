#import "@preview/codelst:2.0.2": sourcecode

#import "conf.typ" : conf
#show: conf.with(
  title: [АНАЛИЗ СЛОЖНОСТИ СОРТИРОВОК, НЕ ИСПОЛЬЗУЮЩИХ СРАВНЕНИЕ ЭЛЕМЕНТОВ],
  type: "referat",
  info: (
      author: (
        name: [Толстова Роберта Сергеевича],
        faculty: [КНиИТ],
        group: "251",
        sex: "male"
      ),
      inspector: (
        degree: "доцент, к. ф.-м. н.",
        name: "М. И. Сафрончик"
      )
  ),
  settings: (
    title_page: (
      enabled: true
    ),
    contents_page: (
      enabled: true
    )
  )
)


#set text(font: "Times New Roman", size : 14pt)
#set par(
  justify : true,
  first-line-indent: 1.25cm,
  leading: 14pt,
  spacing: 14pt
)


= Сортировка подсчётом

== Реализация на C++
#v(1em)

```cpp
void countingSort(vector<int>& arr) {
    if (arr.empty()) return;

    int maxVal = *max_element(arr.begin(), arr.end());
    int minVal = *min_element(arr.begin(), arr.end());
    size_t range = maxVal - minVal + 1;

    vector<int> count(range, 0);

    for (int num : arr) count[num - minVal]++;

    size_t arrIndex = 0;
    for (size_t i = 0; i < range; ++i) {
        while (count[i] > 0) {
            arr[arrIndex++] = i + minVal;
            count[i]--;
        }
    }
}
```

== Анализ сложности
#v(1em) #h(1.25cm)
*Проверка на пустой массив:*

O(1) — проверка на пустой массив занимает постоянное время.

*Поиск минимального и максимального элемента:*

O(n) — проходим по всему массиву для нахождения минимального и максимального элементов (n --- количество элементов в массиве).

*Создание вспомогательного массива для подсчёта:*

O(k), где k — это разница между максимальным и минимальным элементами. В худшем случае $k tilde n$

*Подсчет вхождений каждого элемента:*

O(n) — снова проходим по всему массиву и увеличиваем соответствующие счетчики.

*Перезапись исходного массива в отсортированном порядке:*

O(n + k) — проходим по счетчикам по счетчику, который имеет размер k, и восстанавливаем элементы исходного массива. В коде это вложенные циклы ```cpp for``` и ```cpp while```

*Общая временная сложность:*

O(n + k), n — количество элементов в исходном массиве, k — разница между максимальным и минимальным элементами.


= Поразрядная сортировка

== Реализация на C++
#v(1em)

```cpp
void countingSortForRadix(vector<int>& arr, int exp) {
    size_t n = arr.size();
    vector<int> output(n);
    vector<int> count(10, 0);

    for (size_t i = 0; i < n; i++) count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++) count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (size_t i = 0; i < n; i++) arr[i] = output[i];
}

void radixSort(vector<int>& arr) {
    if (arr.empty()) return;

    int maxVal = *max_element(arr.begin(), arr.end());

    for (int exp = 1; maxVal / exp > 0; exp *= 10) countingSortForRadix(arr, exp);
}
```

== Анализ сложности
#v(1em) #h(1.25cm)
*Проверка на пустой массив:*

O(1) -- проверка на пустой массив занимает постоянное время.

*Поиск максимального элемента*

O(n) -- это ситуация в худшем случае

*Проходы по разрядам*

O(n*d), где d -- число разрядов в максимальном числе, а n -- число элементов в массиве

*Общая временная сложность*

O(n*d) + O(n) + O(1) = O(n*d)
