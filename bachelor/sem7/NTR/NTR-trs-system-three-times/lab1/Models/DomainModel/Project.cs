using System.Collections.Generic;

namespace lab1.Models.DomainModel
{
    public class Project
    {
        public string Name { get; }
        public string Owner { get; }
        public int Budget { get; }
        public bool IsActive { get; }
        public List<string> Categories { get; }
        public List<string> Participants { get; }

        public Project(string name, string owner, int budget, bool isActive, List<string> categories, List<string> participants = null)
        {
            Name = name;
            Owner = owner;
            Budget = budget;
            IsActive = isActive;
            Categories = categories ?? new List<string>();
            Participants = participants ?? new List<string>();
        }

        public Project Inactive()
        {
            return new Project(this.Name, this.Owner, this.Budget, false, this.Categories, this.Participants);
        }
    }
}