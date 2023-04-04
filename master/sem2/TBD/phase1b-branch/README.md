# Etap 1b - sprawozdanie

4. Co wykonywane jest w pierwszym kroku “Set up job” ?

Następuje inicjalizacja obrazu, na którym zostanie wykonane zdefiniowane przez nas workflow. Zostają pobrane odpowiednie *actions*, które umożliwają wykonanie pożądanych przez nas kroków/skryptów.

6. Potwierdź, że przechodzi terraform init.

Przechodzi, ale trzeba było zmienić nr grupy w zmiennych, żeby wykrywało kubełek.

7. Które zmienne trzeba było dodać?

- TF_VAR_group_id
- TF_VAR_billing_account
- TF_VAR_tbd_semester

8. Napisz co trzeba było wykonać (żeby zniknęły błędy i warningi w `Run TFLint`)

Trzeba było pozbyć się zmiennych: `zone`, `environment`, `billing_account`, `group_id`

12. Podaj co jest najdroższym a co najtańszym składnikiem infry.

- najtańszy: kubełki, ceny w zależności od zużycia to groszowe sprawy:
```
  Monthly cost depends on usage

    + Storage (standard)
      Monthly cost depends on usage
        +$0.023 per GiB

    + Object adds, bucket/object list (class A)
      Monthly cost depends on usage
        +$0.05 per 10k operations

    + Object gets, retrieve bucket/object metadata (class B)
      Monthly cost depends on usage
        +$0.004 per 10k operations

    + Network egress
    
        + Data transfer to worldwide excluding Asia, Australia (first 1TB)
          Monthly cost depends on usage
            +$0.12 per GB
    
        + Data transfer to Asia excluding China, but including Hong Kong (first 1TB)
          Monthly cost depends on usage
            +$0.12 per GB
    
        + Data transfer to China excluding Hong Kong (first 1TB)
          Monthly cost depends on usage
            +$0.23 per GB
    
        + Data transfer to Australia (first 1TB)
          Monthly cost depends on usage
            +$0.19 per GB
```
- najdroższy: `GKE`:
```
+ module.gke.google_container_cluster.primary
  +$73.00

    + Cluster management fee
      +$73.00

```

- nie wiadomo jak z `dataproc`, ponieważ nie jest jeszcze wspierany:
```
∙ 1 is not supported yet, see https://infracost.io/requested-resources:
  ∙ 1 x google_dataproc_workflow_template
```


13. Opisz jak się zmieniły koszty i z czego te zmiany wynikają.

Zmieniły się tylko koszty kubełków:
- `Storage`: z `+$0.023 per GiB` do `2.30$`
- `class A`: z `+$0.05 per 10k operations` do `0.20$`
- `class B`: z `+$0.004 per 10k operations` do `+$0.01`

Zmiany te wynikają z założenia "z góry" ilości wykorzystanych zasobów.

**W podobny sposób spróbuj podać szacunki dla pozostałych zmiennych i pokaż wyniki.**

Dodaliśmy: 
```
  google_container_cluster.primary: 
    nodes: 4 
    node_pool[0]:
      nodes: 2 

  google_container_node_pool.primary_preemptible_nodes:
    nodes: 4
```
jednak nie miały one przełożenia na wyliczenia.

Dodaliśmy też:
```
    monthly_egress_data_transfer_gb:  # Monthly data transfer from Cloud Storage to the following, in GB:
      same_continent: 550  # Same continent.
      worldwide: 12500     # Worldwide excluding Asia, Australia.
      asia: 1500           # Asia excluding China, but including Hong Kong.
      china: 50            # China excluding Hong Kong.
      australia: 250       # Australia.
```
dla `google_storage_bucket` i szacunki znacząco wzrosły, mianowicie:
```
    + Network egress
    
        + Data transfer in same continent
          $0.00
    
        + Data transfer to worldwide excluding Asia, Australia (first 1TB)
          +$123
    
        + Data transfer to worldwide excluding Asia, Australia (next 9TB)
          +$1,014
    
        + Data transfer to worldwide excluding Asia, Australia (over 10TB)
          +$181
    
        + Data transfer to Asia excluding China, but including Hong Kong (first 1TB)
          +$123
    
        + Data transfer to Asia excluding China, but including Hong Kong (next 9TB)
          +$52.36
    
        + Data transfer to China excluding Hong Kong (first 1TB)
          +$11.50
    
        + Data transfer to Australia (first 1TB)
          +$47.50
```

14. Zidentyfikuj pozostałe błędy i dodaj odpowiednią zmianę w terraformie aby go naprawić.

poza wymienionymi w poleceniu, trzeba było jeszcze dodać `CKV_GCP_78: "Ensure Cloud storage has versioning enabled"` dla kubełków.
