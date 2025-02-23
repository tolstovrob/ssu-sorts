import matplotlib
import matplotlib.pyplot as plt
import pickle

quicksort = [6.6, 13.91, 74.73, 161.8]
mergesort = [7.45, 15.14, 81.31, 164.92]
heapsort = [11.2, 24.03, 140.74, 302.66]
labels = ['50 000', '100 000', '500 000', '1 000 000']

fig = plt.figure(figsize=(10, 8))

plt.plot(1, 1, 1)
plt.plot(labels, quicksort, marker='o', color='green', label='Быстрая сортировка')
plt.plot(labels, mergesort, marker='o', color='blue', label='Сортировка слиянием')
plt.plot(labels, heapsort, marker='o', color='red', label='Пирамидальная сортировка')
plt.title('Сравнение быстрой сортировки, сортировки слиянием и пирамидальной сортировки')
plt.xlabel('Число элементов')
plt.ylabel('Время (мс)')
plt.legend(loc='best')

pickle.dump(fig, open("figure.pickle", "wb"))

plt.tight_layout()
plt.show()
