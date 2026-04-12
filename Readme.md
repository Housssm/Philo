
*This project has been created as part of the 42 curriculum by hoel-har.*

# Philosophers

## Description

Ce projet s'inspire du probleme du « diner des philosophes », enonce par Edsger Dijkstra.
Des philosophes sont assis autour d'une table avec une assiette de spaghettis et des fourchettes partagees.

L'objectif est de synchroniser les actions des philosophes pour eviter les blocages et empecher qu'un philosophe meure de faim.

## Regles du probleme

- Chaque philosophe dispose d'une assiette .
- Les fourchettes sont partagees entre deux philosophes voisins.
- Un philosophe alterne entre trois etats : manger, dormir, penser.
- Un philosophe ne peut effectuer qu'une seule action a la fois.
- Pour manger, un philosophe doit prendre ses deux fourchettes.
- Quand un philosophe mange, ses deux voisins ne peuvent pas utiliser les fourchettes concernees.
- Les philosophes ne communiquent pas entre eux.

## Objectif

Garder tous les philosophes en vie en respectant les contraintes de temps et de synchronisation.


## Instruction

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parametres

- `number_of_philosophers` : nombre de philosophes.
- `time_to_die` : temps maximal (en ms) sans manger avant qu'un philosophe meure.
- `time_to_eat` : temps (en ms) passe a manger.
- `time_to_sleep` : temps (en ms) passe a dormir.
- `number_of_times_each_philosopher_must_eat` (optionnel) : nombre de repas a atteindre pour chaque philosophe.

## Ressources

- The Code Vault (YouTube) : https://youtu.be/d9s_d28yJq0?si=1g724UBkMsLMC_iM
- Medium - Philosophers 42 Guide : https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2
- Medium - The Dining Philosophers : https://medium.com/@jalal92/the-dining-philosophers-7157cc05315
 