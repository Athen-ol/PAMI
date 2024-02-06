# PAMI
PAMI (Petit Actionneur Mobile Indépendant) est un petit robot composée de moteurs dc, une ESP32 et un L298N pour participer à la coupe de France de robotique.
![IMG_20240201_210901](https://github.com/Athen-ol/PAMI/assets/132818672/ff48916f-d8fb-46dc-a35d-511bec7a6be7)

### Composition :
* ESP32 DEVKIT V1 microcontroleur
* L298N pont en H de controle moteurs DC
* Moteurs N20 6-12V x2
* Supports de moteurs x2
* Batterie LiPo 5-12V (ici 7,4V)
* Perfboard
* Chassis en impression 3D

### Fonctionnement :
Le PAMI communique en bluetooth avec un smartphone qui envoie des caractères comme commande avec l'application Bluetooino.
Il a des commandes analogiques avec les fonctions `avancer(int vit_mot_1, int vit_mot_2)` et `reculer(int vit_mot_1, int vit_mot_2)`
