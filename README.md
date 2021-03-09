# Corewar
Usage: Git clone 'repository path' 'file name'
# Subject
Ce projet permet de créer une "arène" virtuelle (VM) dans laquelle vont se battre des programmes aussi appellé champion.

Ces champions sont codés en instructions assembleurs, ils nous faut donc d'abord les compiler en binaire avant de commencer.
On crée ensuite une arene virtuelle dans laquelle les champions vont se battre, dans cette arène on traitera les instructions de chaque processus.
Si un processus n'a pas donné signe de vie avec l'instruction "live" avant le prochain CYCLE_TO_DIE il sera "tué".
Le dernier processus en vie fait gagné son champion.
