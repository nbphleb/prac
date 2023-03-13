#ifndef BUFFER_H
#define BUFFER_H

#include <QObject>
#include <QDebug>

namespace Numbers
 {

 template <typename T> class Buffer
 {
 public:
     Buffer( int length )
         : length_( length )
     {
         //Данные
         data_ = new T[length_];

         //Размер массива состояний
         stateLength_ = ( length / 32 ) + ( (length % 32) > 0 ? 1 : 0 );

         state_ = new quint32[stateLength_];
         initMask();
         initStates();
     }

     virtual ~Buffer()
     {
         delete []data_;
         delete []state_;
     }

     bool indexInRange( int index ) const
     {
         return index >= 0 && index < length_;
     }

     /*!
      * \brief Добавление нового элемента. Новый элемент располагается на свободном месте
      * \param d
      * \return Индекс нового элемента в массиве
      */
     int append( const T & d )
     {
         int index = occupyIndex();
         if ( index >= 0 && index < length_ )
         {
             data_[index] = d;
         }
         return index;

     }

     /*!
      * \brief addData - Добавление нового элемента
      * \param d - Данные
      * \return Индекс в массиве, где располагается новый элемент
      */
     int addItem( const T & d )
     {
         int index = occupyIndex();
         if ( index >= 0 && index < length_ )
         {
             data_[index] = d;
         }

         return index;
     }

     /*!
      * \brief freeItem - Освободить элемент массива данных
      * \param index - индекс элемента в массиве, которой был возвращен функцией append
      */
     void removeAt( int index )
     {
         freeIndex( index );
     }

     /*!
      * \brief at - Элемент
      * \param index - индекс элемента в буфере, который был возвращен функцией append
      * \return - элемент
      */
     T at( int index ) const
     {
         return data_[index];
     }

     /*!
      * \brief Список элементов
      * \return
      */
     QList<T> listData() const
     {
         QList<T> d;
         for ( int i = 0; i < stateLength_ ; i++ )
         {
             for ( int l = 0; l < 32; l++ )
             {
                 if ( ( state_[i] & ( 1 << l ) ) != 0 && ( i*32 + l ) < length_ )
                 {
                     d << data_[i*32+l];
                 }
             }
         }

         return d;
     }

     /*!
      * \brief Печать индексов занятых элементов
      */
     void printBusyIndices()
     {
         qDebug() << "length "<<length_<<"; state length "<<stateLength_;
         qDebug() << "BUSY:";
         for ( int i = 0; i < stateLength_; i++ )
         {
             for ( int l = 0; l < 32; l++ )
             {
                 if ( (( state_[i] & ( 1 << l ) ) != 0) && ((i*32 +l) < length_) )
                 {
                     qDebug() << "  "<<(i*32+l);
                 }
             }
         }

     }


 private:
     /*!
                 *Инициализация и заполнение массива маски
                 */
     void initMask()
     {
         int count = length_ % 32;
         lastMask_ = 0xFFFFFFFF;
         if ( count != 0 )
         {
             //старшие биты заполнить 0
             for ( int i = 0; i < count; i++ )
             {
                 lastMask_ &= ~( 1 << i );
             }
         }
     }

     /*!
                 *Инициализация массива состояний
                 */
     void initStates()
     {
         for ( int i = 0; i < stateLength_-1; i++ )
         {
             state_[i] = 0;
         }

         state_[stateLength_-1] = lastMask_;
     }


     /*!
                 * \brief occupyIndex - Занять свободный индекс и получить его номер
                 * \return - Индекс, который можно занять, если есть свободные индексы, иначе -1
                 */
     int occupyIndex()
     {
         quint32 m = 0;

         int l;
         for ( l = 0; l < stateLength_; l++ )
         {
             m = state_[l] ^ 0xFFFFFFFF;
             if ( m != 0 )
             {
                 for ( int k = 0; k < 32 && (l*32+k) < length_; k++ )
                 {
                     if ( (state_[l] & (1 << k )) == 0 )
                     {
                         state_[l] |= (1<<k);
                         return l * 32 + k;
                     }
                 }
             }
         }

         return -1;
     }

     /*!
                 * \brief freeIndex - Освободить индекс
                 * \param index - Индекс, который надо освободить
                 */
     void freeIndex( int index )
     {
         int sindex = index / 32;
         int bindex = index % 32;

         state_[sindex] &= ~(1<<bindex);
     }

     /*!
      * \brief length_ - Максимальное количество элементов в буфере
      */
     int 	length_;

     /*!
      * \brief stateLength_ - Длина массива состояний
      */
    int	stateLength_;

     /*!
      * \brief lastMask_ - Маска последнего элемента массива состояний
      */
     quint32	lastMask_;

     /*!
      * \brief state_ - Массив состояний индексов в буфере
      */
     quint32	* state_;

     /*!
      * \brief data_ - Массив данных
      */
     T	* data_;
 };
 }

#endif // BUFFER_H
