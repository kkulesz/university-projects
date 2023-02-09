using System.Collections.Generic;
using System;

using lab1.Models.DomainModel;

namespace lab1.Models.ViewModel
{
    public class MonthSummary
    {
        public List<ProjectActivities> ProjectActivitiesList { get; }
        public UsersMonth Month { get; }

        public MonthSummary(List<ProjectActivities> projectActivitiesList, UsersMonth month)
        {
            ProjectActivitiesList = projectActivitiesList;
            Month = month;
        }
    }

    public class ProjectActivities
    {
        public string ProjectName { get; }
        public List<Activity> Activities { get; }
        public ProjectActivities(string projectName, List<Activity> activities)
        {
            ProjectName = projectName;
            Activities = activities;
        }
    }
}