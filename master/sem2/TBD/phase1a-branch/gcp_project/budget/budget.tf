# https://registry.terraform.io/providers/hashicorp/google/latest/docs/resources/billing_budget

resource "google_billing_budget" "budget" {
  billing_account = var.billing_account
  display_name = "TBD billing budget"

  amount {
    specified_amount {
      currency_code = "USD"
      units = tostring(var.amount) #  TODO or 5000?
    }
  }

  threshold_rules {
    threshold_percent = 0.5
  }

  threshold_rules {
    threshold_percent = 0.8
  }

  threshold_rules {
    threshold_percent = 1.0
  }
}