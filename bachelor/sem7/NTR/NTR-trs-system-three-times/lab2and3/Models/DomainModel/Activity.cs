using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using Microsoft.EntityFrameworkCore;

namespace lab2and3.Models.DomainModel
{
    public record Activity
    {
        public int Id { get; init; }
        public string Code { get; init; }
        public string Project { get; init; }
        public string Executor { get; set; }
        public int Budget { get; set; }
        public Nullable<int> AcceptedBudget { get; set; }
        public DateTime Date { get; set; }
        public List<Activity> Subactivities { get; init; }
        public string Description { get; set; }
        public bool IsActive { get; set; }

        public DateTime CreatedAt { get; init; } = DateTime.Now;
        public DateTime Lab2Field { get; init; } = DateTime.Now;

        [ConcurrencyCheck]
        [DatabaseGenerated(DatabaseGeneratedOption.Computed)]
        public DateTime RowVersion { get; set; }

        public Activity() { }

        private Activity(Activity acc, Nullable<int> acceptedBudget, bool isActive)
        {
            Id = acc.Id;
            Code = acc.Code;
            Project = acc.Project;
            Executor = acc.Executor;
            Budget = acc.Budget;
            AcceptedBudget = acceptedBudget;
            Date = acc.Date;
            Subactivities = acc.Subactivities;
            Description = acc.Description;
            IsActive = isActive;
        }

        public Activity AcceptBudget(int acceptedBudget)
        {
            return new Activity(this, acceptedBudget, this.IsActive);
        }

        public Activity Inactive()
        {
            return new Activity(this, this.AcceptedBudget, false);
        }
    }
}