resource "google_project_service" "dataproc-service" {
  for_each                   = toset(["dataproc.googleapis.com", "workflowexecutions.googleapis.com"])
  project                    = var.project_name
  service                    = each.value
  disable_dependent_services = true
}

resource "google_dataproc_workflow_template" "dataproc_workflow_template" {
  depends_on = [google_project_service.dataproc-service]
  project    = var.project_name
  name       = "${var.project_name}-workflow"
  location   = var.region
  placement {
    managed_cluster {
      cluster_name = "${var.project_name}-cluster"
      config {
        gce_cluster_config {
          metadata = {
            "PIP_PACKAGES" = "synapseml==0.9.5 h2o_pysparkling_3.1"
          }
          zone = var.zone
        }
        initialization_actions {
          executable_file   = "gs://goog-dataproc-initialization-actions-${var.region}/python/pip-install.sh"
          execution_timeout = "600s"
        }
        staging_bucket = var.staging_bucket
        master_config {
          num_instances = 1
          machine_type  = "n1-standard-2"
          disk_config {
            boot_disk_size_gb = 30
          }
        }
        worker_config {
          num_instances = 6 # must be >=2, let's keep it =6 so we have the same as in GKE
          machine_type  = "n1-standard-2"
          disk_config {
            boot_disk_size_gb = 30
          }
        }
        software_config {
          image_version = "2.0.39-ubuntu18"
          properties = {
            "dataproc:dataproc.logging.stackdriver.enable"            = "true"
            "dataproc:dataproc.logging.stackdriver.job.driver.enable" = "true"
            "dataproc:jobs.file-backed-output.enable"                 = "true"
            "dataproc:pip.packages"                                   = "pyspark==3.3.1,pysparkling==0.6.2,synapse==2.121.0"
          }
        }
      }
    }
  }
  jobs {
    step_id = "${var.project_name}-job"
    pyspark_job {
      main_python_file_uri = var.py_file
      properties = {
        "spark.jars.packages" : "com.microsoft.azure:synapseml_2.12:0.9.5-13-d1b51517-SNAPSHOT",
        "spark.jars.repositories" : "https://mmlspark.azureedge.net/maven",
        "spark.jars.excludes" : "org.scala-lang:scala-reflect,org.apache.spark:spark-tags_2.12,org.scalactic:scalactic_2.12,org.scalatest:scalatest_2.12",
        "spark.yarn.user.classpath.first" : "true",
        "spark.dynamicAllocation.enabled" : "false"
        "spark.sql.catalogImplementation" : "in-memory"
      }
    }

  }
}
