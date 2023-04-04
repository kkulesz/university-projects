output "spark_status" {
  value = google_dataproc_job.spark_job_point_8.status[0].state
}