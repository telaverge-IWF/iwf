#ifndef __DCCA_TEST_H__
#define __DCCA_TEST_H__

#define INITIAL     1
#define UPDATE      2
#define TERMINATION 3
#define EVENT       4

extern "C"
{

int DisplayDccaMenuTest();

int SendDccaMessageServer(int input, int index ); 

int SendCreditControlRequestTest( int requestType, int);

int DisplayDccaMenuTestServer(int *);


int SendCreditControlAnswerTest(const diameter::CommandImpl* impl, const int input, ITS_UINT index);

}

#endif
