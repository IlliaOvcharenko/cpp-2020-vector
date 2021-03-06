# Написати свій повноцінний аналог std::vector -- my_vector (подробиці -- найближчі заняття).
   Цей шаблон класу:
- повинен бути коректним,
- надавати гарантії щодо виключень,
- бути достатньо швидким, відтворюватиме логіку збільшення буферу із std::vector, хоча використовувати коефіцієнт 2 -- не обов'язково. Можна дати можливість ним керувати -- статично (аргументом шаблону) чи динамічно.
- Не створюватиме зайві порожні об'єкти і не "затягуватиме" час життя об'єктів, вже видалених із вектора.
- Не заморочуємося кастомними алокаторами, що є в стандартному std::vector.
  З першої спроби дуже мало кому вдасться зробити все правильно. Тому над цією роботою працюватимемо ітеративно. Ваш шаблон повинен бути достатньо щільно покритий тестами (самописними чи із використанням gtest).
  Необхідний функціонал (див. також https://en.cppreference.com/w/cpp/container/vector):
- Конструктор по замовчуванню; конструктор, що створює вектор із n копій переданого елемента; конструктор, який копіює інтервал, заданий ітераторами; конструктор із списку ініціалізації.
- Конструктори копіювання та переміщення.
- Деструктор.
- Оператори присвоєння та присвоєння із переміщенням.
- Оператор звертання за індексом, operator[]  без перевірки виходу за межі (можливо, крім відладочної версії) та метод at(), який кидатиме виключення при виході за межі, front() та back().
- Ітератори, сумісні із адаптерами стандартної бібліотеки та методи для роботи із ними (begin(), end(), cbegin(), cend(), rbegin(), rend(), rcbegin(), rcend()).
- is_empty(), (стандартна назва таки невдала), size(), reserve(), capacity(), shrink_to_fit().
- swap().
- clear(), resize().
- insert(), у двох варіантах, перший приймає ітератор, куди вставляти і значення, другий -- ітератор, куди вставляти та пару ітераторів -- звідки брати. Повинна повертати ітератор на перший вставлений елемент.
- erase() -- аналогічно, в двох варіантах, для видалення одного елементу і інтервалу. Повертає ітератор на перший залишений елемент.
- pop_back() -- викидає останній елемент, (не повертаючи його), push_back() та  emplace_back().
- Оператори ==, !=, <, <=, >, >=, порівняння лексикографічне.
