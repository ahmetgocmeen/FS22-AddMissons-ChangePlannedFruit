#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

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
    sprintf(saveGameDir,"%s\\savegame%d\\missions.xml",gameDir,saveGame);


    int select;
    printf("1- Add Mission\n");
    printf("2- Change Planned Fruit\n");
    printf("Select: ");
    scanf("%d",&select);

    switch (select)
    {
    case 1:
        missionAdder(saveGameDir);
        break;
    case 2:
        changePlannedFruit();
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

void changePlannedFruit()
{

}