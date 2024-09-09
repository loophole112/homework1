#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAGIC_MATERIAL_NAME 100
#define MAGIC_ROLES 100000
#define MAGIC_MATERIALS 100000
#define DENIZENS 200000
#define MAGIC_UPDATES 200000


struct magMatForRole {
    char matName[MAGIC_MATERIAL_NAME];
    long long amountNeeded;
};

struct role {
    int materialsNeeded;
    struct magMatForRole * itemList;
};

struct magMatForList {
    char matName[MAGIC_MATERIAL_NAME];
    long long totalAmountNeeded;
    long long magicRequired;
};

struct updateVariables{
    long long denizens;
    long long denizenRole[DENIZENS];

};

long long calculateTotalMagic(struct magMatForList * materialList, struct role * roles, struct updateVariables * update, struct magMatForRole * materialRole, int roleAmount, int numOfMaterials){
    long long totalMagic = 0;

    printf("Material List:\n");
    for (int i = 0; i < numOfMaterials; i++) {
        printf("Material %s: Magic Required = %lld\n", materialList[i].matName, materialList[i].magicRequired);
    }

    printf("Roles:\n");
    for (int i = 0; i < roleAmount; i++) {
        printf("Role %d:\n", i);
        for (int j = 0; j < roles[i].materialsNeeded; j++) {
            printf("  Material %s: Amount Needed = %lld\n", roles[i].itemList[j].matName, roles[i].itemList[j].amountNeeded);
        }
    }

    for(int i = 0; i < update->denizens; i++){
        for(int j = 0; j < roleAmount; j++){
            if(update->denizenRole[i] - 1 == j){
                for(int k = 0; k < roles[j].materialsNeeded; k++){
                    for(int l = 0; l < numOfMaterials; l++){
                        if(strcmp(materialList[l].matName, roles[j].itemList[k].matName) == 0){
                                totalMagic += roles[j].itemList[k].amountNeeded * materialList[l].magicRequired;
                        }
                    }
                }
            }
        }
    }
    return totalMagic;
}


int main(){
    int roleAmount, materialAmount, updateAmount, numOfMaterials = 0, updateType;
    struct role * roles;
    struct magMatForRole * materialRole;
    struct magMatForList * materialList;
    struct updateVariables update;

    scanf("%d", &roleAmount);

    roles = (struct role *)malloc(roleAmount * sizeof(struct role));
    materialList = (struct magMatForList *)malloc(MAGIC_MATERIALS * sizeof(struct magMatForList));



    for(int i = 0; i < roleAmount; i++){
        scanf("%d", &roles[i].materialsNeeded);
        roles[i].itemList = (struct magMatForRole *)malloc(roles[i].materialsNeeded * sizeof(struct magMatForRole));
        for(int j = 0; j < roles[i].materialsNeeded; j++){
            scanf("%s %lld", roles[i].itemList[j].matName, &roles[i].itemList[j].amountNeeded);
            int identical = 0;
            for(int k = 0; k < MAGIC_MATERIALS; k++){
                if(strcmp(roles[i].itemList[j].matName, materialList[k].matName) == 0){
                    identical = 1;
                    materialList[k].totalAmountNeeded += roles[i].itemList[j].amountNeeded;
                    break;
                }
            }
            if(identical == 0){
                strcpy(materialList[numOfMaterials].matName, roles[i].itemList[j].matName);
                materialList[numOfMaterials].totalAmountNeeded = roles[i].itemList[j].amountNeeded;
                numOfMaterials++;
            }
        }
    }
    materialRole = (struct magMatForRole *)malloc(numOfMaterials * sizeof(struct magMatForRole));

    for(int i = 0; i < numOfMaterials; i++){
        scanf("%s %lld", materialRole[i].matName, &materialRole[i].amountNeeded);
        for(int j = 0; j < numOfMaterials; j++){
            if(strcmp(materialRole[i].matName, materialList[j].matName) == 0){
                materialList[j].magicRequired = materialRole[i].amountNeeded;
                break;
            }
        }
    }


    scanf("%lld", &update.denizens);
    for(int i = 0; i < update.denizens; i++){
        scanf("%lld", &update.denizenRole[i]);
    }
    printf("%lld\n", calculateTotalMagic(materialList, roles, &update, materialRole, roleAmount, numOfMaterials));
    printf("role amount: %d\n", roleAmount);
    scanf("%lld", &updateAmount);
    printf("role amount: %d\n", roleAmount);
    for(int i = 0; i < updateAmount; i++){
        scanf("%d", &updateType);
        char updateName[101];
        long long updateRole, roleAmountChange, magicAmountChange;
        if(updateType == 1){
            scanf("%s %lld", updateName, &magicAmountChange);
            for(int j = 0; j < numOfMaterials; j++){
                if(strcmp(updateName, materialList[j].matName) == 0)
                    materialList[j].magicRequired = magicAmountChange;
            }

            printf("%lld\n", calculateTotalMagic(materialList, roles, &update, materialRole, roleAmount, numOfMaterials));
        } else if(updateType == 2){
            scanf("%lld %s %lld", &updateRole, updateName, &roleAmountChange);
            for(int j = 0; j < numOfMaterials; j++){
                if(strcmp(updateName, roles[updateRole - 1].itemList[j].matName) == 0){
                    roles[updateRole - 1].materialsNeeded = roleAmountChange;
                }
            }

            printf("%lld\n", calculateTotalMagic(materialList, roles, &update, materialRole, roleAmount, numOfMaterials));
        }
    }

    for(int i = 0; i < roleAmount; i++)
        free(roles[i].itemList);
    free(roles);
    free(materialList);
    free(materialRole);

    return 0;
}
