using lab2and3.Models.DomainModel;

namespace lab2and3.Models.ViewModel
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