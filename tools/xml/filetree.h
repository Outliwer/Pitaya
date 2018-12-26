#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QtCore/QVector>
#include <QtXmlPatterns/QSimpleXmlNodeModel>

class FileTree : public QSimpleXmlNodeModel
{
public:
    FileTree(const QXmlNamePool &namePool);

    QXmlNodeModelIndex nodeFor(const QString &fileName) const;

    //! [0]
    virtual QXmlNodeModelIndex::DocumentOrder compareOrder(const QXmlNodeModelIndex&, const QXmlNodeModelIndex&) const;
    virtual QXmlName name(const QXmlNodeModelIndex &node) const;
    virtual QUrl documentUri(const QXmlNodeModelIndex &node) const;
    virtual QXmlNodeModelIndex::NodeKind kind(const QXmlNodeModelIndex &node) const;
    virtual QXmlNodeModelIndex root(const QXmlNodeModelIndex &node) const;
    virtual QVariant typedValue(const QXmlNodeModelIndex &node) const;
    //! [0]
protected:
    //! [1]
    virtual QVector<QXmlNodeModelIndex> attributes(const QXmlNodeModelIndex &element) const;
    virtual QXmlNodeModelIndex nextFromSimpleAxis(SimpleAxis, const QXmlNodeModelIndex&) const;
    //! [1]

private:
    //! [4]
    enum Type {
        File,
        Directory,
        AttributeFileName,
        AttributeFilePath,
        AttributeSize,
        AttributeMIMEType,
        AttributeSuffix
    };
    //! [4]

    inline QXmlNodeModelIndex nextSibling(const QXmlNodeModelIndex &nodeIndex,
                                          const QFileInfo &from,
                                          qint8 offset) const;
    inline const QFileInfo &toFileInfo(const QXmlNodeModelIndex &index) const;
    inline QXmlNodeModelIndex toNodeIndex(const QFileInfo &index,
                                          Type attributeName) const;
    inline QXmlNodeModelIndex toNodeIndex(const QFileInfo &index) const;

    /*
     One possible improvement is to use a hash, and use the &*&value()
     trick to get a pointer, which would be stored in data() instead
     of the index.
    */
    //! [2]
    mutable QVector<QFileInfo>  m_fileInfos;
    const QDir::Filters         m_filterAllowAll;
    const QDir::SortFlags       m_sortFlags;
    QVector<QXmlName>           m_names;
    //! [2]
};

    //! [3]
    //! [3]
