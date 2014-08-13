#ifndef __MYTEXTCODEC_H
#define __MYTEXTCODEC_H
#include <QTextCodecPlugin>
class MyCodecPlugin:public QTextCodecPlugin
{
	public:
		MyCodecPlugin(QTextCodecPlugin *parent = 0);
		virtual QList<QByteArray> names() const;
		virtual QTextCodec *createForName(const QByteArray &name);
		virtual QList<QByteArray> aliases () const;
		virtual QList<int> mibEnums () const;
		virtual QTextCodec *createForMib ( int mib );
};
#endif
