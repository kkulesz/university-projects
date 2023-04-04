resource "google_dataproc_cluster" "dataproc_cluster_point_8" {
  name   = "dataproc-cluster-point-8"
  region = var.region

    project        = var.project_name
  #   staging_bucket = var.bucket

  cluster_config {
    autoscaling_config {
      policy_uri = google_dataproc_autoscaling_policy.dataproc_autoscaling_policy_point_8.name
    }
  }
}


resource "google_dataproc_autoscaling_policy" "dataproc_autoscaling_policy_point_8" {
  policy_id = "dataproc-policy-point-8"
  location  = var.region
  project   = var.project_name

  worker_config {
    max_instances = 3
  }

  basic_algorithm {
    yarn_config {
      graceful_decommission_timeout = "30s"

      scale_up_factor   = 0.5
      scale_down_factor = 0.5
    }
  }
}

resource "google_dataproc_job" "spark_job_point_8" {
  region       = google_dataproc_cluster.dataproc_cluster_point_8.region
  force_delete = true
  project = var.project_name
  placement {
    cluster_name = google_dataproc_cluster.dataproc_cluster_point_8.name
  }

  spark_config {
    main_class    = "org.apache.spark.examples.SparkPi"
    jar_file_uris = ["file:///usr/lib/spark/examples/jars/spark-examples.jar"]
    args          = ["250000"]

    properties = {
      "spark.logConf" = "true"
    }

    logging_config {
      driver_log_levels = {
        "root" = "INFO"
      }
    }
  }
}
