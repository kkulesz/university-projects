# https://developer.hashicorp.com/terraform/language/values/variables

variable "billing_account" {
  type        = string
  description = "To which billing account should the alarms be applied to"
}

variable "budget_name" {
  type = string
}

variable "amount" {
  type        = number
  description = "Amount of the budget"
}

