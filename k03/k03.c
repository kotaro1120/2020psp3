#include <stdio.h>
#include <string.h>
#define DEBUG

#define ALPHABET_LEN    255

char StrOriginal[] = "On a dark deseart highway, cool wind in my hair.";
char StrKey[] = "wind";

char* ForceSearch(char text[], char key[])
{
    //  ここを実装する
    int i,pos,newindex,index,keyindex,textlen=strlen(text),keylen=strlen(key);
    int table[256];

    for(i=0;i<256;i++){
        table[i]=keylen;
    }   

    for(i=0;i<keylen;i++){
        table[(int)key[i]]=keylen-(i+1);
    }

    newindex=keylen-1;
    while(newindex<textlen){
        index=newindex;

        for(keyindex=keylen-1;keyindex>=0;keyindex--,newindex--){
            if(text[newindex]==key[keyindex]){
                if(keyindex==0){
                    return text+newindex;
                }
            }
            else{
                break;
            }
        }
        
    newindex=index+table[(int)text[index]];

        if(index>=newindex){
            newindex=index+1;
    }
}
return NULL;
}

int main(void)
{
    char*   str;
    str = ForceSearch(StrOriginal, StrKey);
    printf("Force Search. Find keyword at:%s\n", str);

    str = BMSearch(StrOriginal, StrKey);
    printf("BM Search. Find keyword at:%s\n", str);

    return 0;
}