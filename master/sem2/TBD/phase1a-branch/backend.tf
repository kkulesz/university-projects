terraform {
  backend "gcs" {
    bucket = "tbd-2022z-8-state"
    prefix = "env/dev"
  }
}
