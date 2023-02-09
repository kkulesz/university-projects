using Microsoft.EntityFrameworkCore;

using lab2and3.Models.DomainModel;

namespace lab2and3.Models.Repositories
{
    public class TrsContext : DbContext
    {
        public DbSet<User> Users { get; set; }
        public DbSet<UsersMonth> UsersMonths { get; set; }
        public DbSet<Project> Projects { get; set; }
        public DbSet<Activity> Activities { get; set; }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseMySQL("server=localhost;database=NTR;user=NTR;password=123456789");
        }
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);
        }
    }
}