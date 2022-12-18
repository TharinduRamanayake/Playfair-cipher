#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void UserInput( char *UserKey,char *UserText,int *Choice)
{


    printf("\n\n\t\t<------------------------------AA1846------------------------------>");
    printf("\n\t\t<---------------------*** Play fair Cipher ***--------------------->\n");
    printf("\t\t<--------------------Also Can Encrypt & Decrypt-------------------->\n\n");


    printf("\n>>>Choice 1 --> Encryption\n");
    printf("\n>>>Choice 2 --> Decryption\n");
    printf("\n>>>Choice 0 --> EXIT  \n");

    printf("\n Enter Your Choice-->");
    scanf("%d",Choice);
    printf("\n Please Enter Your Key here-->");
    scanf("%s",UserKey);
    printf("\n Enter String-->");
    scanf(" %[^\n]%*c",UserText);

}


char* ForGridArray(char* UserKey){
    static char GridArray[26];
    char nUserKey[10];
    char* dUserKey;
    char alphabet[26]={'A','B','C','D','E','F','G','H','I','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','\0'};

    int j=0;
    //Remove All duplicate Keys
    for(int i=0; i<strlen(UserKey); i++){
        if(UserKey[i]=='j' ||UserKey[i]=='J'){
            UserKey[i]='i';
        }else if( UserKey[i] == UserKey[i+1]){//m o o n
            nUserKey[j]=UserKey[i];//o
            j++;
            i++;
            continue;
        }else if(UserKey[i]=='j' ||UserKey[i]=='J'){
            UserKey[i]='i';
        }else if( UserKey[i] == UserKey[i+1]){//m o o n
            nUserKey[j]=UserKey[i];//o
            j++;
            i++;
            continue;
        }else{
            nUserKey[j]=UserKey[i];//m,n
            j++;
        }
    }
    nUserKey[j]='\0';
    dUserKey=strupr(nUserKey);

    //Change Simple keys to Capital keys
    for(int i=0; i<= strlen(dUserKey); i++){
        for(int k=0; k<25; k++ ){
            if(dUserKey[i] == alphabet[k] ){
                alphabet[k]='0';
                continue;
            }
        }
    }



    for(int i=0;i<strlen(dUserKey);i++)
    {//Input your key in grid
        GridArray[i]=dUserKey[i];
    }
    int cache=strlen(dUserKey);

    //add to grid
    for(int i=0; i<25;i++){
        if(alphabet[i]=='0'){
            continue;
        }else{
        GridArray[cache]=alphabet[i];
        cache++;
        }
    }
    GridArray[25]='\0';
    return GridArray;
}

char* UserTextBuild(char* UserText)
{
    static char str[1024];
    char* cache=strupr(UserText);

    //convert j to i
    for(int i=0; i<strlen(cache);i++)
    {
        if(cache[i]=='J')
        {
            cache[i]='I';
        }
    }

   //break UserText  and find same letters
    int j=strlen(cache);
    int l=0;
    for(int i=0; i<=j;i++)
    {
        if(cache[i]==cache[i+1])
            {
                str[l]=cache[i];
                str[l+1]='X';
                l+=2;
            //for encrypted value
            }

        else if(cache[i]!=cache[i+1] && cache[i+1]!='\0')
        {
            str[l]=cache[i];
            str[l+1]=cache[i+1];
            l+=2;
            i++;

            //fadd encrypted letters
        }else if(cache[i]!='\0' &&cache[i+1]=='\0')
            {
                str[l]=cache[i];
                str[l+1]='X';
                str[l+2]='\0';
                break;
            }
    }

    return str;
}

int* playFairIndex( int grid[5][5],char dUserText[1024])
{
    //Add letters and save letters
    static int decUserText[1024];
    int j=0;
    for(int p=0;p<strlen(dUserText);p++){
        for(int k=0; k<5;k++){//raw
            for(int i=0;i<5;i++){//column
                if(dUserText[p]==grid[k][i])
                {
                    decUserText[j]=k;
                    decUserText[++j]=i;
                    ++j;
                    break;
                }
                else
                {
                    continue;
                }
            }
        }
    }
    return decUserText;
}

void main()
{

    while(1)
    {
        int Choice;
        char UserKey[10];
        char  UserText[1024];
        char* dUserText;
        int* index;//decrypt text
        char ddUserText[1024];
        char* GridArray;
        int grid[5][5];

        UserInput(UserKey, UserText, &Choice);
        GridArray=ForGridArray(UserKey);

        int cache=0;
        int q=0;
        printf("\n\t<<<<<-----5*5 PlayFair Grid----->>>>>\n");
        for(int i=0;i<5;i++){
            printf("\n\n\t");
            for(int k=0;k<5;k++){
                cache=GridArray[q];
                grid[i][k]=cache;
                printf("%c\t",grid[i][k]);
                q++;
            }
        }
        printf("\n");

        if(Choice==1)
        {
            dUserText=UserTextBuild(UserText);
            int x;
            for(int i=0;dUserText[i]!='\0';i++){
                ddUserText[i]=dUserText[i];
                if((dUserText[i+1])=='\0'){
                ddUserText[i+1]='\0';
                x=i+1;
                }
            }
            index=playFairIndex(grid,ddUserText);
            char output[1024];//Output
            int j=0;
            for(int i=0; i<2*x; i+=4){
                if(index[i+1]==index[i+3])
                    //for encrypting
                {
                    int column=index[i+1]%5;
                    int raw1=((index[i])+1)%5;
                    int raw2=((index[i+2])+1)%5;
                    output[j]=grid[raw1][column];
                    output[++j]=grid[raw2][column];
                    ++j;
                }
                else if(index[i]==index[i+2])
                {
                    int raw=index[i]%5;
                    int column1=((index[i+1])+1)%5;
                    int column2=((index[i+3])+1)%5;
                    output[j]=grid[raw][column1];
                    output[++j]=grid[raw][column2];
                    ++j;
                }

                else
                {
                    int raw1=index[i]%5;
                    int raw2=(index[i+2])%5;
                    int column1=(index[i+1])%5;
                    int column2=(index[i+3])%5;
                    output[j]=grid[raw1][column2];
                    output[++j]=grid[raw2][column1];
                    ++j;
                }
            }

        output[j]='\0';
        printf("\n>>>Encrypted String is --> %s \n\n",output);

        }
        else if(Choice==2)
        {
            index=playFairIndex(grid,UserText);
            char output[1024];//result
            int j=0;
            for(int i=0; i<(strlen(UserText)*2); i+=4)
            {
                if(index[i+1]==index[i+3])
                {
                    int column=index[i+1]%5;
                    int raw1=(4+index[i])%5;
                    int raw2=(4+index[i+2])%5;
                    output[j]=grid[raw1][column];
                    output[++j]=grid[raw2][column];
                    ++j;
                }
                else if(index[i]==index[i+2])
                {
                    int raw=index[i]%5;
                    int column1=(4+index[i+1])%5;
                    int column2=(4+index[i+3])%5;
                    output[j]=grid[raw][column1];
                    output[++j]=grid[raw][column2];
                    ++j;
                }
                else
                {
                    int raw1=index[i]%5;
                    int raw2=(index[i+2])%5;
                    int column1=(index[i+1])%5;
                    int column2=(index[i+3])%5;
                    output[j]=grid[raw1][column2];
                    output[++j]=grid[raw2][column1];
                    ++j;
                }

            }
            output[j]='\0';
            printf("\n>>>Decrypted String Is --> %s \n\n",output);
        }
        else if(Choice==0)
            {
                printf("\n\n\t\t <<<----See you Again--->>>");
                break;
            }

        else if(Choice!=1||2||0)
            {
                printf("\n\n\t<<---Invalid Syntax--->>>\n\n");
                return 0;
            }

        else continue;

    }
}



