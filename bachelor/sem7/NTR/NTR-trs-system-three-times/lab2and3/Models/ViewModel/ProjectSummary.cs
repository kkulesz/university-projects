using System.Collections.Generic;
using System;

using lab2and3.Models.DomainModel;

namespace lab2and3.Models.ViewModel
{
    public class ProjectSummary
    {
        public string ProjectName { get; }
        public bool IsActive { get; }
        public int OwnerDefinedBudget { get; }
        public int ParticipantsDefinedBudget { get; }
        public List<Activity> Activities { get; }

        public ProjectSummary(string projectName, bool isActive, int ownerDefinedBudget, int participantsDefinedBudget, List<Activity> activities)
        {
            ProjectName = projectName;
            IsActive = isActive;
            OwnerDefinedBudget = ownerDefinedBudget;
            ParticipantsDefinedBudget = participantsDefinedBudget;
            Activities = activities;
        }
    }
}