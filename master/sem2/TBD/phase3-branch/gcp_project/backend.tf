terraform {
  backend "gcs" {
    bucket = "tbd-2022z-8-gcp-project-state"
    prefix = "env/dev"
  }
}
