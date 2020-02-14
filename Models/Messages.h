#pragma once
//message �ĺϼ������࣬���ڷ���ʱ�Ļ���
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
	Messages(const Messages& m);
	~Messages();
	//Messages(const Messages& m);
	MsgStruct getMessageStruct(int index);
	//void appendMessageStruct()
	void appendMessage(bool is_send_type, Message msg);
	int getMessagesCount();
	Messages operator=(const Messages& msg);
	void markedIsSended(int index);
protected:
	QVector<MsgStruct> messages;
};
