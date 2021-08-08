#include <stdio.h>
void funcA(unsigned char **);
void funcAA(unsigned char *);
void funcB(unsigned char *);
void funcBB(unsigned char *);
void funcC(unsigned char **);
void funcCC(unsigned char ***);
void funcD(unsigned char **);
void funcDD(unsigned char ***);
void funcE(unsigned char **);
void funcEE(unsigned char **);
int main(){
	unsigned char *szA;
	unsigned char *szB;
	unsigned char *szC;
	unsigned char *szD;
	unsigned char *szE;
	printf("nポインタ渡し→malloc→値渡し→内容を編集n");
	funcA(&szA);
	printf("A:%sn",szA);
	printf("n値渡し→malloc→値渡し→内容を編集n");
	funcB(szB);
	printf("B:%sn",szB);
	printf("nポインタ渡し→malloc→ポインタ渡し→内容を編集n");
	funcC(&szC);
	printf("C:%sn",szC);
	printf("nポインタ渡し→ポインタ渡し→malloc→内容を編集n");
	funcD(&szD);
	printf("D:%sn",szD);
	printf("nポインタ渡し→値渡し→malloc→内容を編集n");
	funcE(&szE);
	printf("E:%sn",szE);
}
void funcA(unsigned char **szDoublePointer){
	*szDoublePointer = (unsigned char *)malloc(100);
	memset(*szDoublePointer,"",100);
	funcAA(*szDoublePointer);
	printf("AA:%sn",*szDoublePointer);
}
void funcAA(unsigned char *szPointer){
	strcpy(szPointer,"set funcAA");
}
void funcB(unsigned char *szPointer){
	szPointer = (unsigned char *)malloc(100);
	memset(szPointer,"",100);
	funcBB(szPointer);
	printf("BB:%sn",szPointer);
}
void funcBB(unsigned char *szPointer){
	strcpy(szPointer,"set funcBB");
}
void funcC(unsigned char **szDoublePointer){
	*szDoublePointer = (unsigned char *)malloc(100);
	memset(*szDoublePointer,"",100);
	funcCC(&szDoublePointer);
	printf("CC:%sn",*szDoublePointer);
}
void funcCC(unsigned char ***szTriplePointer){
	strcpy(**szTriplePointer,"set funcCC");
}
void funcD(unsigned char **szDoublePointer){
	funcDD(&szDoublePointer);
	printf("DD:%sn",*szDoublePointer);
}
void funcDD(unsigned char ***szTriplePointer){
	**szTriplePointer = (unsigned char *)malloc(100);
	memset(**szTriplePointer,"",100);
	strcpy(**szTriplePointer,"set funcDD");
}
void funcE(unsigned char **szDoublePointer){
	funcEE(szDoublePointer);
	printf("EE:%sn",*szDoublePointer);
}
void funcEE(unsigned char **szDoublePointer){
	/*この場合はダブルポインタの値渡しであるが *
	 *ダブルポインタ自身を変更してるのではなく、 *
	 *ダブルポインタの実体（ポインタ）を変更しているので *
	 *変更内容が呼び出し元に反映される */
	*szDoublePointer = (unsigned char *)malloc(100);
	memset(*szDoublePointer,"",100);
	strcpy(*szDoublePointer,"set funcEE");
}
