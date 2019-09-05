/******************************************************************************
 * QSkinny - Copyright (C) 2016 Uwe Rathmann
 * This file may be used under the terms of the QSkinny License, Version 1.0
 *****************************************************************************/

#ifndef QSK_LINEAR_BOX_H
#define QSK_LINEAR_BOX_H

#include "QskIndexedLayoutBox.h"

class QSK_EXPORT QskLinearBox : public QskIndexedLayoutBox
{
    Q_OBJECT

    Q_PROPERTY( Qt::Orientation orientation READ orientation
        WRITE setOrientation NOTIFY orientationChanged FINAL )

    Q_PROPERTY( uint dimension READ dimension
        WRITE setDimension NOTIFY dimensionChanged FINAL )

    Q_PROPERTY( qreal spacing READ spacing
        WRITE setSpacing RESET resetSpacing NOTIFY spacingChanged FINAL )

    Q_PROPERTY( Qt::Alignment defaultAlignment READ defaultAlignment
        WRITE setDefaultAlignment NOTIFY defaultAlignmentChanged )

    Q_PROPERTY( Qt::Edges extraSpacingAt READ extraSpacingAt
        WRITE setExtraSpacingAt NOTIFY extraSpacingAtChanged )

    Q_PROPERTY( int count READ count )
    Q_PROPERTY( bool empty READ isEmpty() )

    using Inherited = QskIndexedLayoutBox;

  public:
    explicit QskLinearBox( QQuickItem* parent = nullptr );
    explicit QskLinearBox( Qt::Orientation, QQuickItem* parent = nullptr );

    QskLinearBox( Qt::Orientation, uint dimension, QQuickItem* parent = nullptr );
    ~QskLinearBox() override;

    bool isEmpty() const;
    int count() const; // items and spacers

#ifdef QSK_LAYOUT_COMPAT
    int itemCount() const { return count(); }
#endif

    int spacingAtIndex( int index ) const;

    QQuickItem* itemAtIndex( int index ) const;
    int indexOf( const QQuickItem* ) const;

    void removeItem( const QQuickItem* );
    void removeAt( int index );

    qreal heightForWidth( qreal width ) const override;
    qreal widthForHeight( qreal height ) const override;

    Qt::Orientation orientation() const;
    void setOrientation( Qt::Orientation );

    void setDimension( uint );
    uint dimension() const;

    void setExtraSpacingAt( Qt::Edges );
    Qt::Edges extraSpacingAt() const;

    void setDefaultAlignment( Qt::Alignment );
    Qt::Alignment defaultAlignment() const;

    void setSpacing( qreal spacing );
    void resetSpacing();
    qreal spacing() const;

    Q_INVOKABLE int addItem( QQuickItem* );
    Q_INVOKABLE int insertItem( int index, QQuickItem* );

    Q_INVOKABLE int addSpacer( qreal spacing, int stretchFactor = 0 );
    Q_INVOKABLE int insertSpacer( int index, qreal spacing, int stretchFactor = 0 );

    Q_INVOKABLE int addStretch( int stretchFactor = 0 );
    Q_INVOKABLE int insertStretch( int index, int stretchFactor = 0 );

    Q_INVOKABLE void setStretchFactor( int index, int stretchFactor );
    Q_INVOKABLE int stretchFactor( int index ) const;

    void setStretchFactor( const QQuickItem*, int stretchFactor );
    int stretchFactor( const QQuickItem* ) const;

  public Q_SLOTS:
    void transpose();
    void activate();
    void invalidate();
    void clear( bool autoDelete = false );

  Q_SIGNALS:
    void orientationChanged();
    void dimensionChanged();
    void defaultAlignmentChanged();
    void spacingChanged();
    void extraSpacingAtChanged();

  protected:
    bool event( QEvent* ) override;
    void geometryChangeEvent( QskGeometryChangeEvent* ) override;

    void itemChange( ItemChange, const ItemChangeData& ) override;
    void updateLayout() override;

    QSizeF contentsSizeHint() const override;

    void autoAddItem( QQuickItem* ) override final;
    void autoRemoveItem( QQuickItem* ) override final;

  private:
    void removeItemInternal( int index, bool autoDelete );

    class PrivateData;
    std::unique_ptr< PrivateData > m_data;
};

inline bool QskLinearBox::isEmpty() const
{
    return count() <= 0;
}

#endif
