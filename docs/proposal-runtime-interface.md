# Интерфейс секций кода

Пусть у нас есть код

Программа с атомарным счётчиком:

```
func makeAtomicCounter(init int) (sync () int, async async int, async nil) {
    var SyncGet sync int()
    var AsyncGet async async int
    var Inc async nil
    var Val async int
    join {
        case from Inc, from Val as val:
            Val <- val + 1

        case from SyncGet, from Val as val:
            SyncGet <! val
            Val <- val
        case from AsyncGet as ReplyCh, from Val as val:
            // Можно ли здесь объявить Join с участием ReplyCh?
            ReplyCh <- val
            Val <- val
    }
    Val <- init
    return SyncGet, AsyncGet, Inc
}

SyncGet, AsyncGet, Inc := makeAtomicCounter(0)
Inc <- nil
print(SyncGet <- nil)
Inc <- nil
var Result async int
join {
    case from Result as res:
    {
        print(res)
    }
}
AsyncGet <- Result
```

Поскольку у нас ограниченное кол-во базовых типов и, скорее всего, пользовательские типы будут Алгебраическими, то мы сможем вывести по алгоритму [Хиндли-Милнера](https://en.wikipedia.org/wiki/Hindley%E2%80%93Milner_type_system) типы агрументов как у функций, так и у case'ов в join'е.

Тогда секция должна уметь создавать каналы.

```
class Channel {
    bool is_sync;
    Type type;
    Queue<type> msgs;
}
// Type - тип по Хиндли-Милнеру

Channel make_channel(bool is_sync, Type type)
// Channel обёртка для любого канала, по сути работает как shared_ptr.

void register_case(std::vector<Channel> inputs, std::vector<Channel> outputs, Code code)
// Тип Code - это абстракция секции кода, транслируемой из нашего языка. Можем считать, что это функция, которая принимает на вход типы переносимые каналами inputs и каналы outputs по ссылке.
// Добавляется в глобальный регистр реакций. Существует до тех пор, пока все каналы inputs существуют. Продлевает жизнь непустым каналам (msgs > 0)
// Продлевает жизнь каналам в Output с начала выполнения Code до конца

void check_cases()
// Регулярно запускается и проверяет для всех case'ов не существуют ли сообщения для их выполнения.
// Нужен ли рандомизированный порядок обхода???
```

Задачи на ближайшее время.
1. Сделать систему типов (написать классы Type и Object), как она описана в доке Ильи + возможно Алгебраические типы. Нужно уметь в рантайме проверять, принадлежит ли объект типы. Соотвественно для всех базовых типов нужны обёртки. Можно сразу подумать, как перенести в compile time.
2. Сделать хранилище case'ов и написать алгоритм обхода.
3. Написать класс Channel и реализовать глобальный якорь для продления жизни пустым. По хорошему тут прям надо описать state машину состояний канала, чтобы избежать будущих проблем с обращением к удалённой памяти или утечек памяти.
4. Объединить пункты 1-3

Голодание case'а
```
var AlwaysFull1 async int
var AlwaysFull2 async int
var Rare async int
join {
    case from AlwaysFull1 as msg, from Rare as ticket:
    {
        print(res)
    }
    case from AlwaysFull2 as msg, from Rare as ticket:
    {
        print(res)
    }
}
AsyncGet <- Result
```