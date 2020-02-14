#pragma once
//message 的合集数据类，便于发送时的缓存
#include "message.h"

class Messages : public QObject
{
	Q_OBJECT

public:
	struct MsgStruct {
		bool isSendType = false;
		Message msg = Message();
		bool isSended = false;
		Messages::MsgStruct& getMessageStruct(int index);
	};
	Messages(QObject *parent);
	~Messages();
	Messages(const Messages& m);
	MsgStruct getMessageStruct(int index);
	//void appendMessageStruct()
	void appendMessage(bool is_send_type, Message msg);
	int getMessagesCount();
protected:
	QVector<MsgStruct> messages;
};
