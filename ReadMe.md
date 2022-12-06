



### МИНИСТЕРСТВО НАУКИ И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ

### Федеральное государственное автономное образовательное учреждение высшего образования

## Дальневосточный федеральный университет
### ИНСТИТУТ МАТЕМАТИКИ И КОМПЬЮТЕРНЫХ ТЕХНОЛОГИЙ
### Департамент математического и компьютерного моделирования
### ДОКЛАД о практическом задании по дисциплине АИСД

# Дерево Ван Эмде Боаса

### Львов Сергей Николаевич, гр. Б9121-09.03.03пикд

### г. Владивосток, 2022

# Содержание
[*Содержание*](#содержание)

[*1. Введение*](#1-введение)

[*1.1 Применение*](#11-применение)

[*1.2 Неформальная постановка задачи*](#12-неформальная-постановка-задачи)

[*2. Требования к окружению*](#2-требования-к-окружению)

[*2.1 Требования к аппаратному обеспечению*](#21-требования-к-аппаратному-обеспечению)

[*2.2 Требования к программному обспечению*](#22-требования-к-программному-обеспечению)

[*2.3 Требования к пользователям*](#23-требования-к-пользователю)

[*3. Формальное описание алгоритма Дерево Ван Эмде Боаса*](#3-формальное-описание-алгоритма-дерево-ван-эмде-боаса)

[*4. Структура алгоритма*](#4-структура-алгоритма)  

[*5. Реализация алгоритма*](#5-реализация-алгоритма)  

[*5.1 Конструктор*](#51-конструктор)  

[*5.2 Вспомогательные функции*](#52-вспомогательные-функции)  

[*5.3 Empty*](#53-empty)  

[*5.4 Min и max*](#54-min-и-max)  

[*5.5 Find*](#55-find)  

[*5.6 Insert*](#56-insert)  

[*5.7 Remove*](#57-remove)  

[*5.8 Next и Prev*](#58-next-и-prev)


[*Список литературы*](#список-литературы)  

# 1. Введение
При поиске эффективного хранения положительных чисел можно столкнуться с Деревом Ван Эмде Боаса, ключевой особенностью которого является очень быстрое выполнение операция по вставке, удалению поиску чисел за O(n*log(log(U))), где U = $2^k$, где k - максимальное количество бит в числе.
## 1.1 Применение
Кроме очевидного использования дерева Ван Эмде Боаса вставка и хранение элементов за асимптотику, близкую к константе, можно использовать для следующего
1. **Сортировка последовательности за O(n*log(log(U)))**
- Для этого нам достаточно вставить элементы в дерево и запомнить минимальное значение и в цикле вызвать функцию Next от него с увеличением числа x = Next(x+1).
2. **Алгоритм Дейкстры**
- Так как с ипользованием двочиной кучи этот алгоритм работает за O(E*Log(V)), где E - количество ребер между вершинами, V - количество вершин в графе. Если же вместо кучи использовать дерево Ван Емде Боаса, то итоговая асимптотика снизится до O(E*log(log(U)))
## 1.2 Неформальная постановка задачи
Реализовать данную структуру данных, а именно: реализовать все функции, которые используются в данном алгоритме
# 2. Требования к окружению
## 2.1 Требования к аппаратному обеспечению
- наличие персонального компьютера
- большое количество оперативной памяти(Больше 16 гб)
## 2.2 Требования к программному обеспечению
- компилятор для C++
- Git
## 2.3 Требования к пользователю
- уметь компилировать файл
# 3. Формальное описание алгоритма Дерево Ван Эмде Боаса
---
Дерево Ван Эмде Боаса - это структура данных, представляющая собой дерево поиска, которая позволяет эффективно работать с неотрицательными числами в диапазоне  от 0 включительно  до $2^k$ не включительно 
Особенностью этой структуры является то, что операции выполняются за O(log(k)), иначе говоря за асимптотику O(n*log(log(U))) , где k - количество бит в числе, U = $2^k$, что асимптотически лучше, чем O(log(n)) в большинстве других деревьях поиска, где n - количество элементов в дереве.
# 4. Структура алгоритма
Так как дерево хранит числа в интервале от 0 включительно до $2^k$ не включительно, то при k = 1, дерево хранит информацию, содержится ли в нем 0 и 1. Это частный случай.
При k!=1 в дереве будут храниться:
- массив children, состоящий из $2^{k/2}$ элементов
- вспомогательное дерево aux размером k/2 
- минимальное и максимальное значение, хранящаесе в этом дереве, если оно не является пустым.
Таким образом, получается, что структура данных поддерживает себя сама, так как массив children и дерево aux является экземпляром класса Дерева Ван Эмде Боаса.
# 5. Реализация алгоритма
## 5.1 Конструктор
Необходимо реализовать конструктор, который будет соответствовать выше заявленной структуре алгоритма.
Примечательностью данного констурктора является договоренность, что значение *_none* является  таким, что его невозможно получить каким-то другим способом, так как оно является $2^k$, когда дерево позволяет хранить числа  как раз до этого числа не включая его. То есть это значение нам подходит.
``` c++
	VEBTree( int K )
	{	
		_k = K;
		_none = (1 << _k);
		_minValue = _none;
		if ( _k <= 1 )
		{
			aux = NULL;
			children = vector<VEBTree*>( 0 );
		}
		else
		{
			int size = 1 << (_k >> 1);
			children = vector<VEBTree*>( size );
			aux = new VEBTree( _k>>1 );

			for ( int i = 0; i < size; i++ )
			{
			children[i] = new VEBTree( _k >> 1 );
			}
		}
	}

```
## 5.2 Вспомогательные функции
Наша структура предполагает использование битовых операций для разбития и склеивания определенного числа

- Low(ULL x) - функция, которая отсекает от числа x ровно k/2 младших битов
- High(ULL x) - функция, которая отсекает от числа x ровно k/2 старших битов и возвращает число, равное страшим k/2 битам без учета k/2 младших битов
- Merge(ULL high, ULL low) -  функция, которая наоборот соединяет старшие и младшие биты в первоначальный вид
Пример:
x = 11, в двочином виде это 1011
результатом выполнения функции Low(x) будет 3, а функции High(x) будет 2. Таким образом мы разбили наше число на два числа одинаковой k/2 длины
Результатом функции Merge(2,3) будет 11.
```c++
	ULL Low( ULL key )
	{
		return (key & ((1 << (_k / 2)) - 1));
	}
	ULL High(ULL key)
	{
		return (key >> (_k / 2));
	}
	ULL Merge(ULL high,ULL low)
	{
		return (high << (_k / 2) )+low;
	}
```
Последняя функция - Swap(ULL &a, ULL &b), которая меняет значения переменных с помощью третьей переменной
```c++
	void Swap( ULL& a, ULL& b )
	{
		ULL temp = a;
		a = b;
		b = temp;
	}
```
## 5.3 Empty
Проверка на то, является ли дерево пустым или нет, является тривиальной, так как нужно смотреть, не является минимальное число значением _none
```c++
    bool Empty()
    {
        if (this == NULL ||  _minValue == _none )
            return true;
        else 
            return false;
    }
```
## 5.4 Min и max
Реализация функции возврата минимального и максимального значения в дереве является тривиальной задачей, так как мы храним эти значения в дереве и нам нужно лишь вывести поля _minValue и _maxValue
## 5.5 Find
Формальный алгоритм выполнения:
1. Проверить дерево на пустоту. Если пусто, то числа нет
2. Если число равно максимальному или минимальному значению, то это число в дереве есть.
3. В противном случае мы ищем число Low(x) в поддереве ```children[High(x)]```
Таким образом, выполняя операцию Find, мы либо спускаемся по дереву вниз, либо если нашли число, то выходим. На каждом уровне выполняя О(1) операций. В противном случае, если мы спустились до самого низа, k=1 дерева, то мы совершаем O(log(log(U)) действий.
```c++
    bool Find(ULL x )
    {
        if ( Empty() )
        {
            return false; 
        }
        if ( x >= _none ) return false;
        if ( _minValue == x && _maxValue != 0 || _maxValue == x ) return true;
        return children[High(x)]->Find(Low(x));
    }
```
## 5.6 Insert
Формальный алгоритм выполнения:
1. Если дерево пустое, то присовить минимальному и максимальному значению наше число для вставки
2. В противном случае, если наши минимальные и максимальные значения равны, то необходимо выбрать минимальное занчение, между текущим занчением и числом для вставки и аналогично для максимального значения
3. В противном случае, мы меняем значения через функцию Swap, если минимальное значение больше нашего числа для вставки и тоже самое для максимального числа.
4. Если наше дерево не частный случай, то есть k!=1, то мы проверяем на пустоту ребенка для старших битов числа и вставляем их во вспомогательное дерево.
5. Вставляем в массив ребенка по индексу старших битов значение малдших битов.
Ограничения:
- Предполагается, что изначально в дереве нет этого числа, так как повторная вставка уже существующего числа не гарантирует корректность выполнения алгоритма
```c++
	void Insert( ULL x)
	{
		if ( Empty() )
		{
			_minValue = _maxValue = x;

		}
		else
		{
			if ( _minValue == _maxValue )
			{
				_minValue = min( _minValue, x );
				_maxValue = max( _maxValue, x );
			}
			else
			{
				if ( x < _minValue )
				{
					Swap( x, _minValue );
				}
				if ( x > _maxValue )
				{
					Swap( x, _maxValue );
				}
				if ( _k != 1 )
				{
					if ( children[High( x )]->Empty() )
					{
						aux->Insert( High( x ) );
					}
					children[High( x )]->Insert( Low( x ) );
				}   
			}
		}
	}
```
Таким образом, данная операция работает за O(log(log(U))), так как на каждом уровне мы выполняем О(1) операций. Дальше если поддерево ```children[High(x)]``` пусто, то вставка в него за O(1), тк мы выполним всего лишь 1 действие - обновим поля минимального и максимального значения .В итоге каждый раз выполнив O(1) операций, мы переходим к дереву, высота которого на 1 ниже, чем у текущего. Следовательно количество операций пропорционально высоте дерева O(log(k)).
## 5.7 Remove
## 5.8 Next и Prev
## 5.9 Деструктор
# Список литературы
1.	https://neerc.ifmo.ru/wiki/index.php?title=Дерево_ван_Эмде_Боаса#.D0.9F.D1.80.D0.B5.D0.B8.D0.BC.D1.83.D1.89.D0.B5.D1.81.D1.82.D0.B2.D0.B0_.D0.B8_.D0.BD.D0.B5.D0.B4.D0.BE.D1.81.D1.82.D0.B0.D1.82.D0.BA.D0.B8
2.	https://habr.com/ru/post/125499/
3.	https://en.wikipedia.org/wiki/Van_Emde_Boas_tree#Insert
4.	https://ieeexplore.ieee.org/document/9622837
5.	https://iq.opengenus.org/van-emde-boas-tree/
6.	http://web.stanford.edu/class/archive/cs/cs166/cs166.1166/lectures/14/Slides14.pdf
7.	https://www.quora.com/How-is-a-van-Emde-Boas-tree-used-in-practice
8.	https://ocw.mit.edu/courses/6-046j-design-and-analysis-of-algorithms-spring-2015/resources/lecture-4-divide-conquer-van-emde-boas-trees/
9.	https://p2k.unkris.ac.id/IT/en/3065-2962/van-Emde-Boas-tree_15988_p2k-unkris.html
10.	 http://www2.hawaii.edu/~nodari/teaching/s16/notes/notes10.pdf
11.	 https://ru.frwiki.wiki/wiki/Arbre_de_Van_Emde_Boas
12.	 https://wiki5.ru/wiki/Van_Emde_Boas_tree
13.	 https://wikicsu.ru/wiki/Van_Emde_Boas_tree
14.	 https://compscicenter.ru/courses/advanced-algo_part2/2019-spring/classes/4545/
15.	 https://compsciclub.ru/en/courses/advanced-algo_part2/2022-spring/classes/9351/
16.	 https://rsdn.org/forum/alg/4367346.1
17.	 https://examentv.ru/informatika/7820-9-derevo-van-emde-boasa-bystryi-cifrovoi-bor.html
18.	 https://tech.kontur.ru/algorithms-for-everyone
19.	 http://www-di.inf.puc-rio.br/~laber/vanEmdeBoas.pdf
20.	 https://www.isa-afp.org/entries/Van_Emde_Boas_Trees.html
21.	 https://www.isa-afp.org/theories/van_emde_boas_trees/#VEBT_Insert
22.	 https://www.isa-afp.org/theories/van_emde_boas_trees/#VEBT_Delete.html
23.	 https://fileadmin.cs.lth.se/cs/Personal/Rolf_Karlsson/lect12.pdf
24.	 https://bjpcjp.github.io/pdfs/math/van-emde-boas-trees-ITA.pdf
25.	 http://www.cs.tau.ac.il/~zwick/Adv-Alg-2015/van-Emde-Boas.pdf
26.	 http://www14.in.tum.de/lehre/2014WS/ea/split/sec-van-Emde-Boas-Trees-single.pdf
27.	 http://www.cs.cmu.edu/afs/cs/academic/class/15750-s19/ScribeNotes/lecture7.pdf

