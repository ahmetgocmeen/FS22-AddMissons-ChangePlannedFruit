#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LINE 2048

void missionAdder();
void changePlannedFruit();

int main()
{
    char gameDir[1024];
    sprintf(gameDir,"%s\\Documents\\My Games\\FarmingSimulator2022",getenv("USERPROFILE"));


    DIR *dir;
    dir = opendir(gameDir);
    struct dirent *entry;
    int files = 0;

    char tempSaveDir[10][strlen(gameDir)+11];

    
    while( (entry=readdir(dir)))
    {
        if(strstr(entry->d_name,"save") && (strstr(entry->d_name,"Backup") == 0))
        {
            printf("%s\n",entry->d_name);
            sprintf(tempSaveDir[files], "%s\\%s",gameDir,entry->d_name);
            files++;
        }
    }
    
    char saveDir[files][strlen(gameDir)+11];

    for(int i = 0; i<files; i++)
        strcpy(saveDir[i],tempSaveDir[i]);
 
    closedir(dir);

    int saveGame;
    printf("Hangi kayıt için değişiklik yapılacağını seçiniz: ");
    scanf("%d",&saveGame);

    char saveGameDir[strlen(gameDir)+11];
    char save[strlen(gameDir) + 11];

    int select;
    printf("1- Add Mission\n");
    printf("2- Change Planned Fruit\n");
    printf("Select: ");
    scanf("%d",&select);

    switch (select)
    {
    case 1:
        sprintf(saveGameDir,"%s\\savegame%d\\missions.xml",gameDir,saveGame);
        missionAdder(saveGameDir);
        break;
    case 2:
        sprintf(save,"%s\\savegame%d\\",gameDir,saveGame);
        sprintf(saveGameDir,"%s\\savegame%d\\fields.xml",gameDir,saveGame);
        changePlannedFruit(saveGameDir,save,"fields.xml");
        break;
    default:
        break;
    }

}

void missionAdder(char saveGameDir[])
{
    float reward;
    printf("Ödül miktarını giriniz: ");
    scanf("%f",&reward);

    int fieldId;
    printf("Tarla numarası giriniz: ");
    scanf("%d",&fieldId);


    char fruitTypeName[15];
    printf("Meyve türünü giriniz: ");
    scanf("%s",&fruitTypeName);

    char text[5000];
    sprintf(text,"    <mission type=\"harvest\" reward=\"%f\" status=\"1\" success=\"false\">\n        <field id=\"%d\" sprayFactor=\"1.000000\" spraySet=\"false\" plowFactor=\"1.000000\" state=\"2\" vehicleGroup=\"8\" vehicleUseCost=\"379.059998\" growthState=\"8\" limeFactor=\"1.000000\" weedFactor=\"1.000000\" stubbleFactor=\"0.000000\" fruitTypeName=\"%s\"/>\n        <harvest sellPointPlaceableId=\"21\" unloadingStationIndex=\"1\" expectedLiters=\"213619.250000\" depositedLiters=\"0.000000\"/>\n    </mission>\n</missions>",reward,fieldId,fruitTypeName);
    FILE *file;
    file = fopen(saveGameDir,"r+");
    fseek(file, -11, SEEK_END );
    fputs(text, file);
    fclose(file);
}

void changePlannedFruit(char saveGameDir[],char save[],char fileName[])
{
    char tempFileName[strlen(save) + 20];
    strcpy(tempFileName,save);
    strcat(tempFileName,"\\temp_");
    strcat(tempFileName,fileName);



    char buffer[MAX_LINE];

    int fieldId;
    printf("Tarla numarası giriniz: ");
    scanf("%d",&fieldId);


    char fruitTypeName[15];
    printf("Meyve türünü giriniz: ");
    scanf("%s",&fruitTypeName);

    char text[50];
    sprintf(text,"    <field id=\"%d\" plannedFruit=\"%s\"/>\n",fieldId,fruitTypeName);

    fflush(stdin);

    FILE *file;
    FILE *temp;

    file = fopen(saveGameDir,"r");
    temp = fopen(tempFileName,"w");

    bool keep_reading = true;
    int current_line = 1;
    
    do
    {
        fgets(buffer,200,file);

        if(feof(file))
            keep_reading = false;
        else if (current_line == fieldId + 2)
            fputs(text,temp);
        else 
            fputs(buffer,temp);

        current_line++;

    } while (keep_reading);
    
    fclose(file);
    fclose(temp);

    remove(saveGameDir);
    rename(tempFileName,saveGameDir);


}