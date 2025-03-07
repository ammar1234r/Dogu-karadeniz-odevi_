#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>  // bool kutubahanesi

#define FILE_NAME "project2.txt"
#define SHIFT "!~~!"

struct stArea {
    char AreaName[100];
    short Traffic_code;
    bool Is_code_availab;  
};


short ReadPostCode(const char* Message) {
    short PostCode;
    printf("%s", Message);
    scanf("%hd", &PostCode);
    return PostCode;
}


struct stArea Convert_to_Struct(char* word) {
    struct stArea AreaData;
    
    char* pos = strstr(word, SHIFT);
    if (pos != NULL) {
        *pos = '\0';
        strcpy(AreaData.AreaName,word);
        AreaData.Traffic_code = (short)atoi(pos + strlen(SHIFT)); 
    }

    return AreaData;
}


bool IsCity_Availbl(short PostCode, struct stArea* AreaInFile) {
    if (AreaInFile->Traffic_code == PostCode) {
        AreaInFile->Is_code_availab = true;
        return true;
    }
    return false;
}

//klansorde sheir olup olmadigini veriyor
struct stArea ConvertFromFileToStruct() {
    struct stArea AreasInFile;
    AreasInFile.Is_code_availab = false;  
    short PostCode = ReadPostCode("Lütfen bir posta kodu girin: ");
    FILE* file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Dosya aciklanmadi: %s\n", FILE_NAME);
        return AreasInFile;
    }

    
    char line[256];

    while (fgets(line, sizeof(line), file) != NULL) {
       
        AreasInFile = Convert_to_Struct(line);

        if (IsCity_Availbl(PostCode, &AreasInFile)) {
            fclose(file);
            return AreasInFile;
        }
    }

    fclose(file);
    return AreasInFile;
}


int main() {
    struct stArea Area_Information = ConvertFromFileToStruct();

    if (!Area_Information.Is_code_availab) {
        printf("sehir bulunamadi.\n");
    }
    else {
        printf("%s dogu Karadeniz bolgesi bulunuyor.\n", Area_Information.AreaName);
    }

    return 0;
}
