
Базово у героя 100 хп и 20 урона.

# Основной геймплей
Стиль - JRPG (последовательный бой)
## Во время боя: 
### Способности героя:
- Бить (-хп врагу, есть 8% шанс крита)
- Поговорить (у врага есть шкала удобрения, во время действия "говорить" она заполняется на случайное число от 15 до 25, когда шкала заполнится до 100 - бой выигран)
- Юзануть зелье (белый монстр) (+урон, +реген)
- Свалить (после следующего хода противника бой заканчивается)

карта как в Inscription (естественно в 2D)
# Объекты на карте:
## Данж 👿
- Только враги, в конце лут
## Поселение 🏠
- Магазин и тут же регенятся все хп
## Случайные события ❓
- Обмен предмета на случайный
- Казик (даёшь деньги и есть шанс выиграть больше)
- Внезапный враг!
- Костёр с регеном хп


# Предметы:
## Чётки Аида
~ +5 урона
<img width="217" height="213" alt="image" src="https://github.com/user-attachments/assets/9376123d-b11e-4068-8622-3ebcfb624c0e" />
## Дудка Перуна
~ +10 урона
<img width="266" height="206" alt="image" src="https://github.com/user-attachments/assets/0e39305a-4bd9-46b8-bf5c-b456f001f89a" />
## Лапти Таноса
~ +10 хп
<img width="332" height="260" alt="image" src="https://github.com/user-attachments/assets/3e7bf122-ee67-4629-9933-87cb93bc7e27" />
## Калоши Ориона
~ +30 хп
<img width="238" height="215" alt="image" src="https://github.com/user-attachments/assets/104e8f32-d7ed-4795-98db-1229dcc5fde8" />
## Водник Посейдона
~ +5 урон, 5 хп 
<img width="190" height="199" alt="image" src="https://github.com/user-attachments/assets/b84eb531-1686-48d9-856c-330337fdd2fc" />
## Хрустальный клинок
~ +40 урона, -50 хп
## Учебник по риторике
~ +8 к диапазону "случайного удобрения"
<img width="183" height="193" alt="image" src="https://github.com/user-attachments/assets/89d63c0b-5c24-4622-a16e-84138e02d3b5" />



## Метод нанесения урона
int DatPoScham(baseDamage, itemDamage){
  double damage = 0;
  if(rand(0,100) <= 8){
    damage = (baseDamage + itemDamage) * 1,5;
  }
  else{
    damage = baseDamage + itemDamage;
  }
  return static_cast<int>(damage);
}
