using lab1.Models.DomainModel;

namespace lab1.Models.ViewModel
{
    public class ProjectSummaryWithMonth
    {
        public ProjectSummary Summary { get; }
        public UsersMonth Month { get; }

        public ProjectSummaryWithMonth(ProjectSummary summary, UsersMonth month)
        {
            Summary = summary;
            Month = month;
        }
    }

}