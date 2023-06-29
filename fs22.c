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
            sprintf(tempSaveDir[files], "%s\\%s",gameDir,entry->d_name);
            files++;
        }
    }
    
    char saveDir[files][strlen(gameDir)+11];

    for(int i = 0; i<files; i++)
    {
        strcpy(saveDir[i],tempSaveDir[i]);
    }
    closedir(dir);


    int select;
    printf("1- Add Mission\n");
    printf("2- Change Planned Fruit\n");
    printf("Select: ");
    scanf("%d",&select);

    switch (select)
    {
    case 1:
        missionAdder();
        break;
    case 2:
        changePlannedFruit();
        break;
    default:
        break;
    }

}

void missionAdder()
{
    char dene[] = "Deneme\n";
    
    FILE *file;
    file = fopen("missions.xml","r+");
    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];
    fseek(file, -11, SEEK_END );
    fputs("</missions>", file);
   // fprintf(file,"%s",dene);
    fclose(file);
    //while (fgets(buffer, MAX_LENGTH, file))
    //    printf("%s", buffer);
    
}

void changePlannedFruit()
{

}